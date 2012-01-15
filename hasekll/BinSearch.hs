module BinSearch where

search :: Ord a => a -> [a] -> Maybe a
search _ [] = Nothing
search y l
    | y == h = Just y
    | y < h = search y (take (half - 1) l)
    | y > h = search y (drop (half  + 1) l)
    | otherwise = Nothing
  where half = (length l) `div` 2
        h = l !! half