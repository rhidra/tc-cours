-- Type énuméré
data CouleurCarte = Trefle | Carreau | Coeur | Pique
data ValeurCarte = Deux | Trois | Quatre | Cinq | Six | Sept |
                   Huit | Neuf | Dix | Valet | Dame | Roi | As

-- Type tuple
data Carte = Cte ValeurCarte CouleurCarte

--Type tuple polymorphe
data Point a = Pt a a
-- ou
data Point a = Point a a

-- Type énuméré polymorphe
data Shape a = Circle (Point a) a |
            Rectangle (Point a) (Point a)
surface shape = case shape of
    (Circle _ r) -> pi*r²
    (Rectangle (Point x1 y1) (Point x2 y2)) -> (abs(x2-x1))*(abs(y2-y1))

-- Type récursif
data Tree a = Leaf a | Node (Tree a) (Tree a)
flatten tree = f tree []
    where f t lst = case (t, lst) of
        (Leaf x, lst) -> x:lst
        (Node l r, lst) -> f l (f r lst)
-- Appel
flatten (Node (Node (Leaf "a") (Leaf "b")) (Leaf "c"))

-- Synonymes
type String = [Char]
type PhoneNumber = String
type PhoneBook = [(Name,PhoneNumber)]

-- Classe
-- Une classe est un ensemble de types pour lesquels des opérations sont définies
class Eq a where
    (==), (/=) :: a -> a -> Bool
    x /= y = not (x == y)

-- Surcharge
-- Pour implémenter l'égalité : instance de Eq a
instance Eq CouleurCarte where
    c1 == c2 = case (c1,c2) of
        (Trefle, Trefle) -> True
        (Carreau, Carreau) -> True
        (Coeur, Coeur) -> True
        (Pique, Pique) -> True
        (_, _) -> False

-- Héritage
class (Eq a) => Ord a where
    compare              :: a -> a -> Ordering
    (<), (<=), (>=), (>) :: a -> a -> Bool
    max, min             :: a -> a -> a
    --compare est le point de variation
    --il suffit à définir tout le reste

-- Deriving
-- Héritage et surcharge automatique
-- Pas besoin de spécifier la clause instance
data CouleurCarte = Trefle | Carreau | Coeur | Pique
    deriving (Eq, Ord, Enum, Read, Show)
