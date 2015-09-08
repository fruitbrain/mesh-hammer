#lang racket

(provide mesh-data
	 get-vertex
	 get-vertex-count
	 get-vertices
	 get-face
	 get-faces
	 get-face-count
	 get-face-vertex
	 get-face-vertex-all
	 get-face-vertex-count)

(struct mesh-data (vertices faces))

;;; Basic mesh access

(define (get-vertices mesh)
  (mesh-data-vertices mesh))

(define (get-vertex mesh index)
  (vector-ref (get-vertices mesh) index))

(define (get-vertex-count mesh)
  (vector-length (get-vertices mesh)))

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
		     (range 0 (get-face-vertex-count face)))))

(define (get-face-vertex-count face)
  (length face))
