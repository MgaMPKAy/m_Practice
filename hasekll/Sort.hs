module Sort where

insertSort :: Ord a => [a] -> [a]
insertSort [] = []
insertSort (x:xs) = insertIter (x:xs) []
  where 
    insertIter [] acc = acc
    insertIter (x0:xs0) acc = insertIter xs0 (insert x0 acc)
    insert x0 [] = [x0]
    insert x0 l@(y:ys)
        | x0 > y = y : insert x0 ys
        | otherwise = x0:l
