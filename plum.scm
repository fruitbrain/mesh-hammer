;(import chicken scheme foreign)

#>
extern int sdl_init();
extern int sdl_window();
extern int sdl_renderer();
extern int sdl_cleanup();
<#

(define sdl-init     (foreign-lambda int "sdl_init"))
(define sdl-window   (foreign-lambda int "sdl_window"))
(define sdl-renderer (foreign-lambda int "sdl_renderer"))
(define sdl-cleanup  (foreign-lambda int "sdl_cleanup"))
(sdl-init)
(sdl-window)
(sdl-renderer)
;(sdl-cleanup)

