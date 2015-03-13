(require 'clojure.string '[clojure.test :as cljtest] :verbose)
(require '(clojure string [test :as ctest] [string :as string]) :verbose)
(import '(java.util Date GregorianCalendar))
(import 'java.util.Date)


(cljtest/is (= 1 1))
(ctest/is (= 2 2))
(clojure.string/join " " ["name" "address" "city" "state" "zip" "email" "phone"])
(string/join ":" ["name" "address" "city" "state" "zip" "email" "phone"])

(defn class-path
  []
  (let [seqz (.getURLs (java.lang.ClassLoader/getSystemClassLoader))]
    (format "%d paths found" (count (map println seqz)))))

; using leinengen
; ---------------
; $ lein new projectname
; // add the library you need to your project.clj file with
; // a name you choose
; $ lein deps
; // add the jar
; $ lein repl
