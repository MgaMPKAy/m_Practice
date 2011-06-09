max' :: (Ord a) => a -> a ->a
max' a b
     | a > b = a
     | otherwise = b

sum' :: (Num a) => [a] -> a
sum' [] = 0
sum' (x:xs) = x + sum' xs

calcBmis xs = [w / (h * h) | (w, h) <- xs] 

quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) = quicksort (filter (<= x) xs) 
                 ++ [x] 
                 ++ quicksort (filter (> x) xs)

maximum' :: (Ord a) => [a] -> a
maximum' [] = error "No maxmum for empty list"
maximum' [x] = x
maximum' (x:xs)
         | x > max_tail = x
         | otherwise = max_tail
         where max_tail = maximum' xs

replicate' :: (Num i, Ord i) => i -> a -> [a]
replicate' n x
         | n <= 0 = []
         | otherwise = x : replicate' (n - 1) x

hanoi n a b c
      | n == 1 = a ++ "->" ++ c ++ " "
      | otherwise = (hanoi (n - 1) a c b)
                    ++ a ++ "->" ++ c ++ " "
                    ++ (hanoi (n - 1) b a c)

factorial :: Integer -> Integer
factorial 0 = 1
factorial n
          | n > 0 = n * factorial (n - 1)

factorial' n = foldl1 (*) [1..n]

factorial'' n = product [1..n]

factorial''' = product . enumFromTo 1

factorial'''' n = (foldr (.) id [\x -> x * k | k <- [1..n]]) 1

fibs = 0 : 1 : zipWith (+) fibs (tail fibs)

fibs' = 0 : 1 : [a + b | (a, b) <- zip fibs' (tail fibs)]

primes m = 2 : sieve [3,5..m]
       where sieve (x:xs)
                   | x * x > m = x : xs
                   | otherwise = x : sieve (xs [x*x, x*x+2*x..m])