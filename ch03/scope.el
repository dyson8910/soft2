(setq x 10)
(defun foo () (print x))
(foo)
(let ((x 2)) (print x))
(defun bar (z) (let ((x 1) (y 10)) (+ x y z)))
(bar 10)
(defun bar2 (z) (let ((y 10)) (+ x y z)))
(bar2 10)
