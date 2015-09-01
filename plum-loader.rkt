#lang racket

(require ffi/unsafe
	 ffi/unsafe/define)

(define-ffi-definer define-plumloader
  (ffi-lib "libplumloader.so"))

;; Bind CType to struct Mesh
(define-cstruct _Mesh ([read_status _bool]
		       [vertex_count _size]
		       [face_count _size]
		       [vertex_array (_cpointer (_cpointer _float))]
		       [face_array (_cpointer (_cpointer _int))]))

;; Bind functions
(define-plumloader plum_loader (_fun _string -> _Mesh))
(define-plumloader delete_mesh (_fun _Mesh -> _void))

(define mesh (plum_loader "examples/example.plum"))

;; Check for file read status and prevent lock-down
;; (XXX:is this always evaluated?)
(when (eq? (Mesh-read_status mesh) #f)
    (error "what: Failed reading data file!"))

;; Construct a list from data of pointer
;; read from offset begin(included) to end(excluded).
(define (pointer->list p type begin end)
  (if (>= begin (- end 1))
      (list (ptr-ref p type begin))
      (cons (ptr-ref p type begin) (pointer->list p type (+ begin 1) end))))

;; Same with pointer->list, except result is a vector.
(define pointer->vector
  (compose list->vector pointer->list))

;; Extract vertices data from a Mesh object
(define (get-vertices mesh)
  (define vertex-count (Mesh-vertex_count mesh))
  (define vertex-array (Mesh-vertex_array mesh))
  (define ptr-array (pointer->vector vertex-array (_cpointer _float) 0 vertex-count))

  (vector-map (lambda (ptr) (pointer->vector ptr _float 0 3)) ptr-array))

;; Extract faces data from a Mesh object
(define (get-faces mesh)
  (define face-count (Mesh-face_count mesh))
  (define face-array (Mesh-face_array mesh))
  (define ptr-array (pointer->vector face-array (_cpointer _int) 0 face-count))
  (define (face-pointer->vector ptr)
    (define size (ptr-ref ptr _int 0))
    (pointer->vector ptr _int 1 (+ size 1)))

  (vector-map face-pointer->vector ptr-array))

;; Free memory of Mesh (important!)
(delete_mesh mesh)

