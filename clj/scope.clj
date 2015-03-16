; (println x) will cause an exception since it is created only after
; the next line.
(def x 10)
(println x) ; this is fine.
