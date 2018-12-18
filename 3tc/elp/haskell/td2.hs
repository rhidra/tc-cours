filter :: (a -> Bool) -> [a] -> [a]
-- Filtre la liste en fonction de la fonction passée en paramètre
-- Ex :
-- filter (\x -> x < 10) [9,10,11,12] = [9]

map :: (a -> b) -> [a] -> [b]
-- Applique une opération à tous les éléments d'une liste
-- Ex :
-- map (\x -> x+1) [1,2,3] = [2,3,4]

[ f x | x <- xs, x < k ]
-- La liste de tous les (f x), telle que x viennent de la liste xs et soit inférieur à k

foldr :: (a -> b -> b) -> b -> [a] -> b
-- Combine les éléments de la liste
-- Paramètres = Fonction de combinaison, valeur initiale, liste
-- Ex :
-- foldr f z [] = z
-- foldr f z (x:xs) = f x (foldr z f xs)
-- La fonction est appliquée à z, puis à l'élément le plus à droite de la liste

foldl :: (b -> a -> b) -> b -> [a] -> b
-- foldl = identique à foldr mais dans l'autre sens
-- fold' = identique à foldl' mais mieux
