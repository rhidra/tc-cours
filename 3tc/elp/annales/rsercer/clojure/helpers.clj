
; fonction qui cherche un caractère dans une chaine
(defn inStr? [str char]
  (cond
    (empty? str) false
    (= char (first str)) true
    :else (inStr? (rest str) char) ))

; fonction pour concatener string
; il existe aussi la fonction clojure.string/join
(defn concatStr [str1 sep str2]
  (if (empty? str1) str2 (str str1 sep str2)))

; pour concatener de listes il existe la fonction
; (concat x y & zs)
; https://clojuredocs.org/clojure.core/concat