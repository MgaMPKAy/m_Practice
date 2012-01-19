module Pearl1 where

import Data.Array
import Data.Array.ST
import Data.List

findGap :: Num b => [b] -> (Bool, b)
findGap l = foldl hasGap (False ,head l) (tail l)
  where
    hasGap (s, a) b
        | s = (s, a)
        | b - a /= 1 = (True, a + 1)
        | otherwise = (False, b)

{--
  worst case: sorted and reversed list [n-1, n-2 .. 0] -> o(n^2)
--}
minfree1 :: [Int] -> Int
minfree1 xs = head ([0..] \\ xs)
  where
    (\\) :: Eq a => [a] -> [a] -> [a]
    us \\ vs = filter (\x -> not $ x `elem` vs) us

{--
  idea: not every number in [0 .. length xs] can be in xs
        smallest number not in xs is the smallest number not in filter (<= n) xs
--}
minfree2 :: [Int] -> Int
minfree2 = search . checklist

search :: Array Int Bool -> Int
search = length . takeWhile id . elems

checklist :: [Int] -> Array Int Bool
checklist xs = accumArray (||) False (0, n)
                    (zip (filter (<= n) xs) (repeat True))
  where n :: Int
        n = length xs

checklist' :: [Int] -> Array Int Bool
checklist' xs = runSTArray $ do
    a <- newArray (0, n) False
    sequence [writeArray a x True | x <- xs, x <= n]
    return a
  where n = length xs

countlist :: [Int] -> Array Int Int
countlist xs = accumArray (+) 0 (0, n) (zip xs (repeat 1))
  where n = length xs

{--
  idea:
  (as ++ bs) \\ cs = (as \\ cs) ++ (bs \\ cs)
  as \\ (bs ++ cs) = (as \\ bs) \\ cs
  (as \\ bs) \\ cs = (as \\ cs) \\ bs
--}

minfree :: [Int] -> Int
minfree xs = minfrom 0 (length xs, xs)

minfrom :: Int -> (Int, [Int]) -> Int
minfrom a (n, xs)
    | n == 0      = a
    | m == b - a  = minfrom b (n - m, vs)
    | otherwise   = minfrom a (m , us)
  where (us, vs)  = partition (< b) xs
        b         = a + 1 + n `div` 2
        m         = length us