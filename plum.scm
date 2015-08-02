;(import chicken scheme foreign)

#>
#include "sdl.hpp"
<#

(define sdl-init       (foreign-lambda int "sdl_init"))
(define sdl-window     (foreign-lambda int "sdl_window"))
(define sdl-renderer   (foreign-lambda int "sdl_renderer"))
(define sdl-loadbitmap (foreign-lambda int "sdl_loadbitmap"))
(define sdl-draw       (foreign-lambda int "sdl_draw"))
(define sdl-cleanup    (foreign-lambda int "sdl_cleanup"))
(display (sdl-init))
(display (sdl-window))
(display (sdl-renderer))
(display (sdl-loadbitmap))
(display (sdl-draw))
(display (sdl-cleanup))
