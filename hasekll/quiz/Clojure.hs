module Clojure where

-- 20
butLast = head . tail . reverse

-- 21
nth l n = head $ drop n l

-- 22
count l = foldr id 0 (map (const (+1)) l)

-- 25
odd' = filter (\x -> x `rem` 2 == 0)

-- 23
reverse' l
    | null l = l
    | otherwise = reverse' (tail l) ++ [head l]
