merge :: (Ord a) => [a] -> [a] -> [a]
merge [] ys = ys
merge xs [] = xs
merge (x:xs) (y:ys)
  | x < y  = x : merge xs (y:ys)
  | x == y = y : merge xs ys
  | x > y  = y : merge (x:xs) ys