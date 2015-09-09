#lang racket

(require ffi/unsafe
	 ffi/unsafe/define
	 ffi/vector
	 ffi/cvector
	 "mesh-data.rkt")

(provide load-mesh
	 _Mesh)

(define _float-ptr 'float-ptr)
(define _int-ptr 'int-ptr)

(define-cstruct _Mesh ([read_status _bool]
		       [vertex_count _size]
		       [face_count _size]
		       [vertex_array (_cpointer _float-ptr)]
		       [face_array (_cpointer _int-ptr)]))

(define-ffi-definer define-plumloader
  (ffi-lib "libplumloader"))

(define-plumloader plum_loader (_fun _string -> _Mesh))
(define-plumloader delete_mesh (_fun _Mesh -> _void))

;; Safer plum-loader that additionally checks for read status
(define (plum-loader path)
  (define loaded-mesh (plum_loader path))
  (begin
    (when (eq? (Mesh-read_status loaded-mesh) #f)
      (error "plum-loader: Failed reading data file!"))
    loaded-mesh))

;; Load Racket mesh object from the data file at path
(define (load-mesh path)
  (mesh-c->racket (plum-loader path)))

;;; Racket mesh to C struct conversion

(define (vertices->ppointer vertices)
  (define vtx-ptr-lst
    (vector->list
     (vector-map list->f32vector vertices)))
  (define untagged-pptr (cvector-ptr (list->cvector vtx-ptr-lst _f32vector)))
  (begin
    (set-cpointer-tag! untagged-pptr _float-ptr)
    untagged-pptr))

(define (faces->ppointer faces)
  (define (prepend-length face)
    (cons (length face) face))
  (define face-ptr-lst
    (vector->list
     ;; For some reason, list->s32vectors converts all s32vector to pointers
     (vector-map (compose list->s32vector prepend-length) faces)))
  (define untagged-pptr (cvector-ptr (list->cvector face-ptr-lst _s32vector)))
  (begin
    (set-cpointer-tag! untagged-pptr _int-ptr)
    untagged-pptr))

(define (mesh-racket->c mesh)
  (let ([vertex_count (get-vertex-count mesh)]
	[face_count (get-face-count mesh)]
	[vertex_array (vertices->ppointer (get-vertices mesh))]
	[face_array (faces->ppointer (get-faces mesh))])
    (make-Mesh #t vertex_count face_count vertex_array face_array)))

;;; C struct to Racket mesh conversion

;; Construct a list from data of pointer
;; read from offset begin(included) to end(excluded).
(define (pointer->list p type begin end)
  (if (>= begin end)
      empty
      (cons (ptr-ref p type begin) (pointer->list p type (+ begin 1) end))))

;; Same with pointer->list, except result is a vector.
(define pointer->vector
  (compose list->vector pointer->list))

;; Extract and convert vertices data from a C mesh object
(define (extract-vertices c-mesh)
  (let* ([vtx-count (Mesh-vertex_count c-mesh)]
	 [vtx-array (Mesh-vertex_array c-mesh)]
	 [vtx-ptr (pointer->vector vtx-array (_cpointer _float) 0 vtx-count)])
    (vector-map (lambda (ptr) (pointer->list ptr _float 0 3)) vtx-ptr)))

;; Extract and convert faces data from a C mesh object
(define (extract-faces c-mesh)
  (define (face-pointer->list ptr)
    (let ([size (ptr-ref ptr _int 0)])
      (pointer->list ptr _int 1 (+ size 1))))
  (let* ([face-count (Mesh-face_count c-mesh)]
	 [face-array (Mesh-face_array c-mesh)]
	 [face-ptr  (pointer->vector face-array (_cpointer _int) 0 face-count)])
    (vector-map face-pointer->list face-ptr)))

;; Convert Mesh C struct object to a Racket mesh-data object
(define (mesh-c->racket c-mesh)
  (begin0
    (mesh-data (extract-vertices c-mesh)
	       (extract-faces c-mesh))
    (delete_mesh c-mesh)))
