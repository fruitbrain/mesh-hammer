#lang racket

(require ffi/unsafe
	 ffi/unsafe/define
	 "mesh-data.rkt")

(provide load-mesh)

(define-ffi-definer define-plumloader
  (ffi-lib "libplumloader.so"))

(define-plumloader plum_loader (_fun _string -> _Mesh))
(define-plumloader delete_mesh (_fun _Mesh -> _void))

;; Safer plum-loader that additionally checks for read status
(define (plum-loader path)
  (define loaded-mesh (plum_loader path))
  (begin
    (when (eq? (Mesh-read_status loaded-mesh) #f)
      (error "plum-loader: Failed reading data file!"))
    loaded-mesh))

;; Construct a list from data of pointer
;; read from offset begin(included) to end(excluded).
(define (pointer->list p type begin end)
  (if (>= begin (- end 1))
      (list (ptr-ref p type begin))
      (cons (ptr-ref p type begin) (pointer->list p type (+ begin 1) end))))

;; Same with pointer->list, except result is a vector.
(define pointer->vector
  (compose list->vector pointer->list))

;; Extract and convert vertices data from a C mesh object
(define (extract-vertices c-mesh)
  (let* ([vtx-count (Mesh-vertex_count c-mesh)]
	 [vtx-array (Mesh-vertex_array c-mesh)]
	 [ptr-array (pointer->vector vtx-array (_cpointer _float) 0 vtx-count)])
    (vector-map (lambda (ptr) (pointer->vector ptr _float 0 3)) ptr-array)))

;; Extract and convert faces data from a C mesh object
(define (extract-faces c-mesh)
  (define (face-pointer->vector ptr)
    (let ([size (ptr-ref ptr _int 0)])
      (pointer->vector ptr _int 1 (+ size 1))))
  (let* ([face-count (Mesh-face_count c-mesh)]
	 [face-array (Mesh-face_array c-mesh)]
	 [ptr-array  (pointer->vector face-array (_cpointer _int) 0 face-count)])
    (vector-map face-pointer->vector ptr-array)))

;; Load Racket mesh object from the data file at path
(define (load-mesh path)
  (define c-mesh (plum-loader path))
  (begin0
    (mesh-data (extract-vertices c-mesh)
		 (extract-faces c-mesh))
    (delete_mesh c-mesh)))
