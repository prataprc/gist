(defn multi-arity
  ;; 3-arity arguments and body
  ([first-arg second-arg & third-arg]
    (do-things first-arg second-arg third-arg))
  ;; 2-arity arguments and body
  ([first-arg second-arg]
    (do-things first-arg second-arg))
  ;; 1-arity arguments and body
  ([first-arg]
    (do-things first-arg)))
