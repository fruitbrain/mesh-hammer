#lang racket

(require ffi/unsafe
	 ffi/unsafe/define)

(define-ffi-definer define-plumgraphics
  (ffi-lib "libplumgraphics"))

(define _Context-pointer (_cpointer 'Context-pointer))

(define-plumgraphics program (_fun -> _int))
(define-plumgraphics initialize (_fun -> _Context-pointer))
(define-plumgraphics probe_event (_fun _Context-pointer -> _int))
(define-plumgraphics poll_events (_fun -> _void))
(define-plumgraphics window_should_close (_fun _Context-pointer -> _bool))
(define-plumgraphics set_window_should_close (_fun _Context-pointer _bool -> _void))

(define NO_EVENT -1)
(define KEY_ESCAPE 256)

;;; Initialize GLFW and show window
(define context (initialize))

;;; Main game loop
(define (game-loop)
  (unless (window_should_close context)
    (poll_events)
    (event-handler (probe_event context))
    (game-loop)))

(define (event-handler event)
  (case event
    [(256) (display "Window close!\n")]))

(game-loop)
