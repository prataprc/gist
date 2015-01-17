(def symbols
  [["shall start with non-numeric character       " 'abcd]
   ["contain alpha-numeric and some special chars " '*special*+!-_?]
   ["namespace qualified name                     " 'namspace/symbol]
   ["qualified class name                         " 'class.property.name]
   [". prefix is reserved                         " '.reserved]
   [". suffix is reserved                         " 'reserved.]
   ["? suffix for boolean checks                  " 'nil?]])

(def literals
  [["number " 100000000000000.1]
   ["string " "hello world"]
   ["boolen " [true false]]
   ["nil    "    nil]
   ["vector " [1 2 3 4]]
   ["map    "    {:a "first" :b 10 "stringkey" :can-be-keyword}]
   ["set    "    #{100000000.1 "str" true false nil [1 2 3] {1 2}}]])

(do
  (println "literals")
  (count (map (fn [eg] (println "  " (eg 0) (eg 1))) literals)))

(do
  (println)
  (println "symbols")
  (count (map (fn [eg] (println "  " (eg 0) (eg 1))) symbols)))
