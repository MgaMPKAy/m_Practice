merge :: (Ord a) => [a] -> [a] -> [a]
merge [] ys = ys
merge xs [] = xs
merge (x:xs) (y:ys)
  | x < y  = x : merge xs (y:ys)
  | x == y = y : merge xs ys
  | x > y  = y : merge (x:xs) ys

hamming = 1 : merge mul2 (merge mul3 mul5)
          where mul2 = map (*2) hamming
                mul3 = map (*3) hamming
                mul5 = map (*5) hamming