
reverseWords :: String -> String
reverseWords line = unwords $ reverse $ words line

primes :: Integral a => [a] -> [a]
primes (x:xs) = x : primes (filter (\y -> y `rem` x /= 0) xs)
lprime :: Integral a => a -> a
lprime n = bigger n (primes [2..])
  where
    bigger n (x:xs)
        | n <= x = head xs
        | otherwise = bigger n xs

data Tree a = Empty | Leaf a | Tree a (Tree a, Tree a) deriving (Show)

insert :: Ord a => a -> Tree a -> Tree a
insert x Empty = Leaf x
insert x (Leaf y) = 
    if x < y 
        then Tree y (Leaf x, Empty)
        else Tree x (Empty, Leaf y)
insert x (Tree a (l, r)) =
    if x > a 
        then Tree a (l, insert x r)
        else Tree a (insert x l, r)

stringToTree :: Ord a => [a] -> Tree a
stringToTree str = foldr insert Empty str