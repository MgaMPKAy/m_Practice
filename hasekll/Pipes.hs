module Pipes where

import Data.List

result0 :: Int
result0 = foldr (+) 0 (map (+2) (filter odd [1..10]))


result2 :: Int
result2 = foldr (+) 0 $ map (+2) $ filter odd [1..10]


result3 :: Int
result3 = foldr (+) 0 . map (+2) . filter odd $ [1..10]


(|>) :: a -> (a -> b) -> b
x |> f = f x

result1 :: Int
result1 =
    [1..10] |> filter odd
            |> map (+2)
            |> foldr (+) 0


(|>>) :: (a -> b) -> (b -> c) -> a -> c
f |>> g = g . f

result4 :: Int
result4 = filter odd |>> map (+2) |>> foldr (+) 0 $ [1..10]


fib :: [Integer]
fib = (0,1) |> unfoldr (\(a,b) -> Just(a, (b, a + b)))

fib' :: [Integer]
fib' = 0 : 1 : zipWith (+) fib' (tail fib')

