#lang racket

(require ffi/unsafe
	 ffi/vector
	 ffi/cvector)

(provide mesh-data
	 get-vertex
	 get-vertices
	 get-face
	 get-faces
	 get-face-count
	 get-face-vertex
	 get-face-vertex-all
	 get-face-vertex-count
	 _Mesh
	 Mesh-read_status
	 Mesh-vertex_count
	 Mesh-face_count
	 Mesh-vertex_array
	 Mesh-face_array
	 make-Mesh)

(struct mesh-data (vertices faces))

;;; Basic mesh access

(define (get-vertices mesh)
  (mesh-data-vertices mesh))

(define (get-vertex mesh index)
  (vector-ref (get-vertices mesh) index))

(define (get-faces mesh)
  (mesh-data-faces mesh))

(define (get-face mesh index)
  (vector-ref (get-faces mesh) index))

(define (get-face-count mesh)
  (vector-length (get-faces mesh)))

(define (get-face-vertex face index vertices)
  (vector-ref vertices (list-ref face index)))

(define (get-face-vertex-all face vertices)
  (list->vector (map (lambda (idx) (get-face-vertex face idx vertices))
		     (range 0 (get-face-vertex-count face)))))	; XXX:inefficient (list->vector)

(define (get-face-vertex-count face)
  (length face))

;;; Racket mesh to C struct conversion

(define _float-ptr 'float-ptr)
(define _int-ptr 'int-ptr)
(define-cstruct _Mesh ([read_status _bool]
		       [vertex_count _size]
		       [face_count _size]
		       [vertex_array (_cpointer _float-ptr)]
		       [face_array (_cpointer _int-ptr)]))

(define (mesh-racket->c mesh)
  (let ([vertices (get-vertices mesh)]
	[faces (get-faces mesh)])
    'undefined))

(define (vertices->ppointer vertices)
  (define vtx-ptr-lst
    (vector->list
     (vector-map list->f32vector vertices)))
  (define untagged-pptr (cvector-ptr (list->cvector vtx-ptr-lst _f32vector)))
  (begin
    (cpointer-push-tag! untagged-pptr _float-ptr)
    untagged-pptr))
