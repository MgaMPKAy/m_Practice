module GS
where

prime0 :: Integral a => a -> Bool
prime0 n
  | n < 1 = error "not a positive integer"
  | n== 1 = False
  | otherwise = ld n == n
    where
      ld n = ldf 2 n
      ldf k n
        | divides k n = k
        | k^2 > n = n
        | otherwise = ldf (k + 1) n
      divides d n = rem n d == 0

sortInts :: [Int] -> [Int]
sortInts [] = []
sortInts xs = m : (sortInts (removeFst m xs))
  where m = minInt xs

minInt [] = error "empty list"
minInt [x] = x
minInt (x:xs) = min x (minInt xs)

removeFst :: Eq a => a -> [a] -> [a]
removeFst a [] = []
removeFst a (x:xs) = if a == x then xs else x : (removeFst a xs)

removeAll :: Eq a => a -> [a] -> [a]
removeAll a [] = []
removeAll a (x:xs) = if a == x then removeAll a xs else x : (removeAll a xs)

removeLast :: Eq a => a -> [a] -> [a]
removeLast a xs = reverse $ removeFst a (reverse xs)

removeCount :: Eq a => Int -> a -> [a] -> [a]
removeCount 0 _ xs = xs
removeCount n a xs = removeCount (n - 1) a (removeFst a xs)

removeMid :: Eq a => [a] -> [a]
removeMid [] = []
removeMid xs = if mod (length xs) 2 == 0 then
                 (take ((div (length xs) 2) - 1) xs ) ++ (drop ((div (length xs) 2) + 1) xs )
               else
                 (take (div (length xs) 2) xs ) ++ (drop ((div (length xs) 2) + 1) xs )