#lang racket

(provide tri-normal
         face-normal
         normalize)

(define (tri-normal tri)
  (define vec1 (map - (second tri) (car tri)))
  (define vec2 (map - (third tri) (car tri)))
  (list (- (* (second vec1) (third vec2)) (* (third vec1) (second vec2))) (- (* (third vec1) (car vec2)) (* (car vec1) (third vec2))) (- (* (car vec1) (second vec2)) (* (second vec1) (car vec2)))))
(define (face-normal facet)
  (if (equal? (length facet) 3) (tri-normal facet) (let ([triangle1 (list (car facet) (second facet) (third facet))]
                                                         [triangle2 (list (car facet) (third facet) (fourth facet))])
                                                         (map + (tri-normal triangle1) (tri-normal triangle2)))))
(define (square i) (* i i))

(define (normalize vec)
  (define size (sqrt (apply + (map square vec))))
  (map (lambda (num) (/ num size)) vec))