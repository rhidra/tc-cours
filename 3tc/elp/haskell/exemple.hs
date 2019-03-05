import Prelude hiding (length, sum, product, and, or, any, all)
inc x = x+1
add x y = x + y

addElemInList elem n list
    | n == 1    = elem:list
    | n > 1     = elem:(addElemInList elem (n-1) list)
    | n <= 0    = list

dupli l = case l of
    (x:[]) -> x:x:[]
    (x:xs) -> x:x:dupli xs

repli l n = case l of
    (x:[]) -> addElemInList x n []
    (x:xs) -> (addElemInList x n []) ++ repli xs n
--
-- compress l = case l of
--     []       -> []
--     (x:[])   -> x:[]
--     (x:x:[]) -> x:[]
--     (x:x:xs) -> x:compress xs
--     (a:b:xs) -> a:compress (b:xs)
--
-- encode l = case l of
--     [] -> []
--     [x] -> (x, 1)
--     (x:xs) -> case res of
--         [] -> (x, 1)
--         (y:ys) -> case y of
--             (elem, nb)
--                 | elem /= x -> (x, 1):res
--                 | otherwise -> (elem, nb+1):ys
--     where res = encode xs

-- TD2

group l = case l of
    [] -> []
    [x] -> [[x]]
    (x:xs) -> (x:(filter (\a -> a == x) xs)):group (filter (\y -> y /= x) xs)

-- encode l = map (compte) (group l)
--     where compte l = case l of
--         [] -> ("x", 0)
--         [x] -> (x, 1)
--         (x:xs) -> (x, compte2 xs 1)
--         where compte2 l n = case l of
--             [] -> n
--             (x:xs) -> compte2 xs n+1

myReverse :: [a] -> [a]
myReverse l = foldl (\xs x -> x:xs) [] l

length l = foldr (\x n -> n+1) 0 l

sum l = foldr (+) 0 l

product l = foldr (*) 1 l

and lst = foldr (&&) True lst

or l = foldr (||) False l

any f l =  or (map f l)

all f l = and (map f l)

-- TD3

data Tree a = Leaf a | Node (Tree a) (Tree a)

-- treeHeight tree = f tree 0
--     where f t h = case t of
--         Leaf _ ->  h+1
--         Node l r -> max (f l h+1) (f r h+1)

data CouleurCarte = Trefle | Carreau | Coeur | Pique
    deriving (Eq, Ord, Enum, Read, Show)
data ValeurCarte = Deux | Trois | Quatre | Cinq | Six | Sept |
                   Huit | Neuf | Dix | Valet | Dame | Roi | As
    deriving (Eq, Ord, Enum, Read, Show)

data Carte = ValeurCarte CouleurCarte
    deriving (Read, Show)
type TasDeCartes = [Carte]


-- TD4

safeHead l = case l of
    [] -> Nothing
    (x:xs) -> Just x

main = do
    -- choix aleatoire d'une carte
    c <- randomIO :: IO Int -- import System.Random
    v <- randomIO :: IO Int -- import System.Random
    let (c', v') = (c `mod` (fromEnum Pique), v `mod` (fromEnum As))
    let laCarte = Carte (toEnum v' :: ValeurCarte)
                        (toEnum c' :: CouleurCarte)
    putStrLn ("indice: " ++ (show laCarte))
    -- jeu de devinette
    jeu laCarte

jeu carteATrouver =
  do
    line <- getLine
    if (read line) `estLaMeme` carteATrouver
      then putStrLn "Vous avez gagne!"
      else do
        putStrLn "Non, reessayez!"
        jeu carteATrouver
