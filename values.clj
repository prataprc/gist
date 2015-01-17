(def vn nil)
(def vs "hello world")
(def vi 10)                     ; java.lang.Long
(def vbi 10000000000000000N)    ; clojure.lang.BigInt
(def vd 10.1)                   ; java.lang.Double
(def vbd 10.11111111111111M)    ; java.math.BigDecimal
(def vr  1/2)                   ; clojure.lang.Ratio
(def vk :keyword)               ; clojure.lang.Keyword
(def vy 'symbolname)            ; clojure.lang.Symbol
(def vv (vector (range 1 1000)) ; clojure.lang.PresistentVector
(def vm (map keyword {:a 1 :b 2 :c 3}  "   (type {:a 1 :b 2 :c 3})) ; clojure.lang.PersistentArrayMap
(def "#{1 2 3}          "   (type #{1 2 3}))    ; clojure.lang.PersistentHashSet
(def "(:a 1 :b 2 :c 3)  "   (type '(:a 1 :b 2 :c 3))) ; clojure.lang.PersistentList

