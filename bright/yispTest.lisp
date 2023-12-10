(def calcHand (fn (list)
    (if (= 10 (car list))
        (+ 10 (car list))
        (+ 50 (car (cdr list)))
    ))
)

(calcHand (0 50))

(let (z (+ 2 3)) (+1 z))

(let (p (+ 2 3) q (+ 2 p)) (+ p q)) 

(def genplus5 (fn () (fn (b) (+ 5 b))))

(def plus5 (genplus5))

(plus5 7)

(def fib (fn (N) (if (= N 0) 1 (if (= N 1) 1 (+ (fib (- N 1)) (fib (- N 2)))))))
(fib 1)
(fib 2)
(fib 4)

(cons 5 (cons 6 ( cons 7 8) ) )