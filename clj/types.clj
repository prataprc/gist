(println "nil               "   (type nil))   ; nil
(println "true              "   (type true))  ; java.lang.Boolean
(println "false             "   (type false)) ; java.lang.Boolean
(println "\"hello world\"     " (type "hello world")) ; java.lang.String
(println "10                "   (type 10))      ; java.lang.Long
(println "10000000000000000N"   (type 100000N)) ; clojure.lang.BigInt
(println "10.1              "   (type 10.1))    ; java.lang.Double
(println "10.11111111111111M"   (type 10.111M)) ; java.math.BigDecimal
(println "1/2               "   (type 1/2))         ; clojure.lang.Ratio
(println ":keyword          "   (type :keyword))    ; clojure.lang.Keyword
(println "'symbolname       "   (type 'symbolname)) ; clojure.lang.Symbol
(println "[1 2 3]           "   (type [1 2 3]))     ; clojure.lang.PresistentVector
(println "{:a 1 :b 2 :c 3}  "   (type {:a 1 :b 2 :c 3})) ; clojure.lang.PersistentArrayMap
(println "#{1 2 3}          "   (type #{1 2 3}))    ; clojure.lang.PersistentHashSet
(println "(:a 1 :b 2 :c 3)  "   (type '(:a 1 :b 2 :c 3))) ; clojure.lang.PersistentList

; Numerical Computation
(* (- (+ 10 10) 10) 10) ; add, sub multiply
(dec (inc 10))
(/ 10 2) ; number
(/ 10 3) ; ratio
(quot 10 3)
(rem 10 3)
(apply min (take 10 (iterate inc 1)))
(apply max (take 10 (iterate inc 1)))

; Auto-promoting computation
(*' (-' (+' 10 10) 10) 100000000000000000)
(dec' (inc' 10))

; Comparison
(== 10 10.0) ; true
(= 10 10.0)  ; false
(< 2 3 4) ; true
(<= 2 2 3) ; true
(> 4 3 2) ; true
(>= 4 4 3) ; true
(zero? 0)
(pos? -1)
(neg? 1)

; Bitwise operations
(bit-and
  bit-or
  bit-xor
  bit-not
  bit-shift-right
  bit-shift-left

; Ratios
numerator denominator

; Coercions
int bigdec bigint double float long num short
