#lang racket/base

(require rackunit
	 ffi/unsafe
	 "mesh-data.rkt"
	 "plum-loader.rkt")

(require/expose "mesh-data.rkt"
		(_float-ptr
		 vertices->ppointer))

(define test-mesh (load-mesh "examples/example.plum"))
(define test-vertices (get-vertices test-mesh))
(define test-face (get-face test-mesh 23))

(test-case
 "Basic mesh access"
 (check-equal? (get-vertex test-mesh 5)
	       '(-0.5 0.5 -0.5))
 (check-equal? (get-face test-mesh 23)
	       '(4 0 11))
 (check-equal? (get-face-count test-mesh)
	       24)
 (check-equal? (get-face-vertex test-face 1 test-vertices)
	       '(-0.5 -0.5 0.5))
 (check-equal? (get-face-vertex-count test-face)
	       3))

(test-case
 "vertices->ppointer returns double pointer?"
 (check-true (cpointer? (vertices->ppointer test-vertices))))
