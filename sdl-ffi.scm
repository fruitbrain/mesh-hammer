#>
#include "sdl.hpp"
<#

(define sdl-init       (foreign-lambda int "sdl_init"))
(define sdl-window     (foreign-lambda int "sdl_window"))
(define sdl-renderer   (foreign-lambda int "sdl_renderer"))
(define sdl-loadbitmap (foreign-lambda int "sdl_loadbitmap"))
(define sdl-draw       (foreign-lambda int "sdl_draw"))
(define sdl-cleanup    (foreign-lambda int "sdl_cleanup"))
