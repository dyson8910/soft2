(setq num 0)
(catch 'loop
  (while t
    (print num)
    (setq num (+ num 1))
    (if (>= num 4) (throw 'loop nil))))

(defun foo (i j) (> i (+ j 2)))
(catch 'loop
  (let ((i 0))
    (while (< i 10)
      (let ((j 0))
	(while (< j 10)
	  (if (foo i j)
	      (throw 'loop (list i j)))
	  (setq j (+ j 1))))
      (setq i (+ i 1)))))

(defun catch2 (tag) (catch tag (throw 'hack 'yes)))
(catch 'hack (print (catch2 'hack)) 'no)
(catch 'hack (print (catch2 'quux)) 'no)
