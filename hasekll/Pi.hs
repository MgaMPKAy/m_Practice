module Pi where

pi' :: Double
pi' = (piLoop 0 0) * width
  where
    piLoop :: Double -> Double -> Double
    piLoop n acc
        | n == numRects = acc
        | otherwise = let mid = (n + 0.5) * width
                          height =  4.0 / (1.0 + mid ^^ 2)
                          in piLoop (n + 1) (acc + height)
    numRects, width :: Double
    numRects = 100000
    width = 1 / numRects
