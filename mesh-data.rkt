#lang racket/base

(provide mesh-data
	 get-vertices
	 get-faces
	 get-vertex
	 get-face)

;; Struct data that represents a mesh
(struct mesh-data (vertices faces))

;; Get vertex list from mesh object
(define (get-vertices mesh)
  (mesh-data-vertices mesh))

;; Get face index list from mesh object
(define (get-faces mesh)
  (mesh-data-faces mesh))

;; Get a vertex of index from mesh object
(define (get-vertex mesh index)
  (vector-ref (get-vertices mesh) index))

;; Get a face of index from mesh object
(define (get-face mesh index)
  (vector-ref (get-faces mesh) index))
