#lang racket

(require ffi/unsafe
	 ffi/unsafe/define)

(define-ffi-definer define-plumgraphics
  (ffi-lib "libplumgraphics"))

(define-plumgraphics program (_fun -> _int))

;(initialize)

(define (game-loop should-stop?)
  (unless should-stop?
    (display "Infinite loop\n")
    (game-loop #f)))

(game-loop #f)
;(program)
