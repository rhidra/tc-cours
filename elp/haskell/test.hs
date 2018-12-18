import Prelude hiding (length, and)

-- Haskell

-- ghci

-- 3 : []
-- Rajoute l'élèment de gauche dans la liste de droite.
-- head donne le premier élèment de la liste.
-- reverse inverse une liste.
-- ++ concatène deux listes.

-- addElemInList => ajoute un élèment un nbre de fois donné dans une liste
addElemInList a n l
  | n == 1  = a : l
  | n > 1   = a : addElemInList a (n-1) l
  | n <= 0  = l

-- dupli => Duplique les éléments de la liste
dupli l = case l of
            [] -> []
            (x:xs) -> x:x:(dupli xs)

-- repli => duplique chaque élèment d'une liste un certain nombre de fois
repli l n = case l of
            [] -> []
            (x:xs) -> addElemInList x n (repli xs n)

-- compress => enlève les duplications consécutives dans une liste
compress l = case l of
  [] -> []
  [x] -> [x]
  (x:x':xs)
    | x == x' -> compress (x':xs)
    | x /= x' -> x:(compress (x':xs))

-- encode
encode lst = case lst of
  [] ->[]
  (x:xs) -> case res of
    [] -> [(1,x)]
    (y:ys) -> case y of
      (nb,elem)
        | elem /= x -> (1,x):res
        | otherwise -> (nb+1,elem):ys
    where res = encode xs

-- group => regroupe chaque caractères ensemble dans un tableau de listes
group lst = case lst of
  [] -> []
  (x:xs) -> (filter (\y -> y == x) lst)
            : (group (filter (\y -> y /= x) lst))

-- encode' => Donne le nombre d'élèment de chaque élément présent dans une liste
-- encode' lst =
--   map (\x -> f 1 x) (group lst)
--     where f n lst = case lst of
--       (x:[]) -> (n+1,x)
--       (x:xs) -> f (n+1) xs

-- quicksort
quicksort lst = case lst of
  [] -> []
  -- (e:xs) -> (quicksort (filter (\x -> x < e) xs))
  --           ++ [e]
  --           ++ (quicksort (filter (\x -> x >= e) xs))
  (x:xs) -> quicksort [y | y <- xs, y < x]
            ++ [x]
            ++ quicksort [y | y <- xs, y >= x]

-- myReverse => Inverse la liste
myReverse lst = foldl (\xs x -> x:xs) [] lst

-- length => Longueur d'une liste
length lst = foldr (\_ l -> l+1) 0 lst

-- and => ET logique
and lst = foldr (&&) True

-- flatten => Aplatis un arbre
data Tree a = Leaf a | Node (Tree a) (Tree a)
flatten tree = f tree []
  where f t lst = case (t,lst) of
                    (Leaf x, lst) -> x:lst
                    (Node l r, lst) -> f l (f r lst)
-- flatten (Node (Node (Leaf "a") (Leaf "b")) (Leaf "c"))

-- treeHeight => Hauteur d'un arbre
treeHeight tree = case tree of
        Leaf a -> 1
        Node l r -> 1 + max (treeHeight l) (treeHeight r)

-- NestedList => Liste pouvant contenir d'autres listes
data NestedList a = Elem a | List [NestedList a]

-- Classe et surcharge
data CouleurCarte = Trefle | Carreau | Coeur | Pique
  deriving (Eq, Ord, Enum, Read, Show)
data ValeurCarte = Deux | Trois | Quatre | Cinq | Six | Sept |
                   Huit | Neuf | Dix | Valet | Dame | Roi | As
  deriving (Eq, Ord, Enum, Read, Show)

data Carte = ValeurCarte CouleurCarte
    deriving (Read, Show)

-- surcharge de l'égalité et de la comparaison
instance Eq Carte where
    (Carte v c) == (Carte v' c') = v == v'
instance Ord Carte where
    compare (Carte v c) (Carte v' c') = compare v v'

type TasDeCartes = [Carte]
