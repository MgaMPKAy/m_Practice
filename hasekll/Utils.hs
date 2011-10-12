module Utils where

import Data.List

mss :: [Integer] -> Integer
mss = maximum.map sum.segments

segments :: [a] -> [[a]]
segments = concat.map inits.tails

segments' :: [a] -> [[a]]
segments' = (filter (not . null)) . segments

powerset :: [a] -> [[a]]
powerset [] = [[]]
powerset (x:xs) = let ps = powerset xs in map (x:) ps ++ ps

quicksort :: Ord a => [a] -> [a]
quicksort [] = []
quicksort (x:xs) = quicksort (filter (<=x) xs) 
                   ++ [x] 
                   ++ quicksort (filter (>x) xs)