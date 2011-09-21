sum_n n = foldr id 0 $ adders n

adders n = [\i -> x + i | x <- [0..n]]
