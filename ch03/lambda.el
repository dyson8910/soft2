(lambda (a b c) (+ a b c))
((lambda (a b c) (+ a b c)) 1 2 3)

(setq f #'(lambda (a b c) (+ a b c)))
(funcall f 1 2 3)
(funcall #'(lambda (a b c) (+ a b c)) 1 2 3)

(require 'cl)
(lexical-let ((counter 0)) (defun new-id () (setq counter (+ counter 1))))

