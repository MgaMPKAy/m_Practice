module Stream where


scaleStream :: Num a => [a] -> a -> [a]
scaleStream s factor = map (factor*) s

-- ex 3.55
partialSum :: Num a => [a] -> [a]
partialSum [] = []
partialSum s@(x:xs)  = x : zipWith (+) (partialSum s) xs


-- ex 3.56
hamming = 1 : merge (merge h2 h3) h5
  where
    h2 = map (2*) hamming
    h3 = map (3*) hamming
    h5 = map (5*) hamming
    merge (x:xs) (y:ys)
        | x < y  = x : merge xs (y:ys)
        | x == y = x : merge xs ys
        | x > y  = y : merge (x:xs) ys
          

-- ex 3.59
integrateSeries :: Fractional c => [c] -> [c]
integrateSeries s = zipWith (*) (factors 1) s
  where 
    factors n = 1 / n : factors (n + 1)

expSeries :: [Double]
expSeries  = 1 : integrateSeries expSeries

sinSeries :: [Double]
sinSeries  = 0 : integrateSeries consSeries

consSeries :: [Double]
consSeries = 1 : integrateSeries sinSeries

-- ex 3.60
mulSeries :: Num a => [a] -> [a] -> [a]
mulSeries s1@(x:xs) s2@(y:ys) = 
    (x * y) : zipWith (+) (map (x*) ys) (mulSeries xs s2)

piStream :: [Double]
piStream = scaleStream (partialSum (piSummands 1)) 4
  where
    piSummands n = 1 / n : map (0-) (piSummands (n + 2))


sqrtStream :: Fractional a => a -> [a]
sqrtStream x = guesses
  where
    guesses = 1 : map improve guesses
    improve guess = 0.5 * (guess + x / guess)

eulerTransform s =
    let s0 = s !! 0
        s1 = s !! 1
        s2 = s !! 2
    in (s2 - ((s2 - s1) ^ 2 / (s0 - 2 * s1 + s2))) : eulerTransform (tail s)

makeTableau transform s =
    s : makeTableau transform (transform s)

acceleratedSequence transform s =
    map head (makeTableau transform s)

-- ex 3.64
ln2 = partialSum (ln2Summands 1)
  where
    ln2Summands n = 1 / n : map (0-) (ln2Summands (n + 1))

ln2' = eulerTransform ln2

ln2'' = acceleratedSequence eulerTransform ln2