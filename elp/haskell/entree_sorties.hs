-- Maybe
safeHead lst = case lst of
    [] -> Nothing
    (x:xs) -> Just x
