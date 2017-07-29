(defun cube (x) (* x x x))
(cube 3)

(defun sum (term a b)
  (if (> a b)
      0
    (+ (funcall term a)
       (sum term (+ a 1) b))))

(defun sum-cubes (a b)
  (sum 'cube a b))
(defun sum-integers (a b)
  (sum 'identity a b))
(sum-cubes 1 10)
(sum-integers 1 10)

