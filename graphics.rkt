#lang racket

(require ffi/unsafe
	 ffi/unsafe/define
	 "plum-loader.rkt")

(define-ffi-definer define-graphics
  (ffi-lib "libplumgraphics.so"))
