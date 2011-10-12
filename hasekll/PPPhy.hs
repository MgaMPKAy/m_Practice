module PPPhy where

{- input -}
u1 = [270, 269, 268, 267, 265]
t1 = [18.44, 17.11, 17.61, 17.56, 18.39]
u2 = [169, 167, 165, 162, 161]
t2 = [19.78, 19.00, 18.92, 19.12, 19.41]
u3 = [212, 211, 210, 209, 208]
t3 = [19.13, 18.93, 18.96, 18.76, 18.34]


{- output -}
-- averU = map average [u1, u2, u3]
averU = [268,165,210]
averT = map average [t1, t2, t3]

{-
averQ = [q1, q2, q3]
     where 
       q1 = average $ zipWith q u1 t1
       q2 = average $ zipWith q u2 t2
       q3 = average $ zipWith q u3 t3
-}
averQ = zipWith q averU averT

n = map (/e0) averQ

roundedN = map round n

averE = zipWith (/) averQ (map fromIntegral roundedN)

thetaE = map abs $ zipWith (-) averE (replicate 3 e0)

m = zipWith  (/) averE (replicate 3 (e0 / m0))

thetaM = map (abs . (m0 -)) m


{- helper -}

q :: Floating a => a -> a -> a
q u t = a / b
    where
      a = 1.02*10**(-14)
      b = u * ((t * (1 + 0.02 * sqrt t)) ** (3/2))


average xs = sum xs / fromIntegral (length xs)

printR :: Show a => [a] -> IO ()
printR = mapM_ print

e0 = 1.6 * 10 ** (-19)

m0 = 9.11*10**(-31)