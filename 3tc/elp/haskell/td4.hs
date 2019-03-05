-- Pour gèrer les erreurs, on peut renvoyer un type Maybe a
minimum :: (Ord a) => [a] -> Maybe a
minimum lst = case lst of
    [] -> Nothing
    l -> Just (minimum' l)
    where minimum' l = case l of
        [x] -> x
        (x:xs) -> min x (minimum' xs)

-- On ne peut pas utiliser la valeur de retour tel quel
Just 5 >>= return . (*2)

-- Les E/S sont étiquettées par le type IO a
getChar :: IO Char
putChar :: Char -> IO ()

-- Pareil avec des strings
getLine :: IO String
putStrLn :: String -> IO ()
