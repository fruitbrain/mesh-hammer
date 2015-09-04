#lang racket/base

(require rackunit
	 "mesh-data.rkt"
	 "plum-loader.rkt")

(define test-mesh (load-mesh "examples/example.plum"))
(define test-vertices (get-vertices test-mesh))
(define test-face (get-face test-mesh 23))

(test-case
 "Basic mesh access"
 (check-equal? (get-vertex test-mesh 5)
	       #(-0.5 0.5 -0.5))
 (check-equal? (get-face test-mesh 23)
	       #(4 0 11))
 (check-equal? (get-face-count test-mesh)
	       24)
 (check-equal? (get-face-vertex test-face 1 test-vertices)
	       #(-0.5 -0.5 0.5))
 (check-equal? (get-face-vertex-count test-face)
	       3))

(test-case
 "Mesh to VBO conversion"
 (check-equal? (vector-length (vboify test-mesh))
	       (* (get-face-count test-mesh) 3 3))
 (check-equal? (vector-flatten #(#(1 2) #(3 4) #(5 6)))
	       #(1 2 3 4 5 6)))
