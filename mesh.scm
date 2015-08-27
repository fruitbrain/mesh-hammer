;; Get vertices list from mesh data.
(define (get-vertices mesh)
  (car mesh))

;; Get vertices normal list from mesh data.
(define (get-vertices-normal mesh)
  (if (> (length mesh) 1)
      (cadr mesh)))

;; Get faces list from mesh data.
(define (get-faces mesh)
  (last mesh))
