#lang racket/base

(require rackunit
	 ffi/unsafe
	 ffi/vector
	 "plum-loader.rkt")

(require/expose "plum-loader.rkt"
		(pointer->list
		 pointer->vector
		 vertices->ppointer))

(define test-svec (s32vector 1 2 3 4 5))
(define test-ptr (s32vector->cpointer test-svec))

(check-equal? (pointer->list test-ptr _int 0 -1)
	      '())
(check-equal? (pointer->list test-ptr _int 0 0)
	      '())
(check-equal? (pointer->list test-ptr _int 0 5)
	      '(1 2 3 4 5))
(check-equal? (pointer->vector test-ptr _int 0 5)
	      #(1 2 3 4 5))
