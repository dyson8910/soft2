(defun ! (n) (if (= n 1) 1 (* n (! (- n 1)))))
(defun factoral (n) (fact-iter 1 1 n))
(defun fact-iter (product counter max-count)
  (if (> counter max-count)
      product
    (fact-iter (* counter product)
	       (+ counter 1)
	       max-count)))

(! 6)
(factoral 6)
