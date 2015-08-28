;; Extends the visibility of the fib function in fib.c to this file.
#>
extern int fib(int n);
<#

;; Declare foreign function xfib which connects with fib.
;; Syntax is as follows:
;;
;; (foreign-lambda RETURNTYPE NAME ARGTYPE ...)
;; whereas RETURNTYPE is the return type of the C function,
;; NAME is the name of the C function wrapped with "",
;; ARGTYPE is the type of the parameters the C function accepts.
;; ... simply states the function can accept multiple ARGTYPEs.
;;
;; Refer to http://wiki.call-cc.org/man/4/Accessing%20external%20objects#foreign-lambda.
(define xfib (foreign-lambda int "fib" int))

;; do function is similar to for(;;) in C.
(do ((i 0 (+ i 1))) ((> i 10))
  (printf "~A " (xfib i)))

;; Print a newline char and end the program.
(newline)
