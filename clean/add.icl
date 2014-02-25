module add

import StdEnv

kahanSum :: [Real] -> Real
kahanSum ls = loop ls 0.0 0.0
  where
    loop [] sum carry = sum
    loop [x:xs] sum carry =
        let y = x - carry
            t = y + sum
        in loop xs t (t - sum - y)

Start =
  let harmonic_double = take 10000 (map (\x -> 1.0 / fromInt x) [1, 2..])
  in (kahanSum harmonic_double, sum harmonic_double)
