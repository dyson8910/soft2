(setq num 0)
(while (< num 4)
  (print num)
  (setq num (+ num 1)))

(require 'cl)
(do ((i 0 (+ i 1))) ((>= i 4)) (print i))
(dotimes (i 4) (print i))
