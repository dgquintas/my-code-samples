(def visitors #{"foo"})

(defn hello
  "writes hello message to *out*. calls you by username.
  knows if you have been here before"
  [username]
  (dosync
    (let [past-visitor (@visitors username)]
      (if past-visitor
        (str "welcome back, " username)
        (do 
          (alter visitors conj username)
          (str "hello, " username))))))
      
