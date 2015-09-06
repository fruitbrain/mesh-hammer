#lang racket

(require ffi/unsafe)

(provide mesh-data
	 _Mesh
	 Mesh-read_status
	 Mesh-vertex_count
	 Mesh-face_count
	 Mesh-vertex_array
	 Mesh-face_array
	 make-Mesh
	 get-vertex
	 get-vertices
	 get-face
	 get-faces
	 get-face-count
	 get-face-vertex
	 get-face-vertex-all
	 get-face-vertex-count
	 vboify
	 vector-flatten)

(struct mesh-data (vertices faces))

;; Binding type for C Mesh struct
(define-cstruct _Mesh ([read_status _bool]
		       [vertex_count _size]
		       [face_count _size]
		       [vertex_array (_cpointer (_cpointer _float))]
		       [face_array (_cpointer (_cpointer _int))]))

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
  (vector-ref vertices (vector-ref face index)))

(define (get-face-vertex-all face vertices)
  (list->vector (map (lambda (idx) (get-face-vertex face idx vertices))
		     (range 0 (get-face-vertex-count face)))))	; XXX:inefficient (list->vector)

(define (get-face-vertex-count face)
  (vector-length face))

;;; Mesh to VBO data conversion

(define (vboify mesh)
  (define vertices (get-vertices mesh))
  (define faces (get-faces mesh))
  (define flatten-me
    (vector-map (lambda (face) (get-face-vertex-all face vertices)) faces))
  (vector-flatten (vector-flatten flatten-me)))

(define (vector-flatten vec)
  (apply vector-append (vector->list vec)))	      ; XXX:inefficient (vector->list)
