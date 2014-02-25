module fft

// Fast Fourier transform

import StdEnv
from StdLib import zipWith

:: Complex = {r :: Real, i :: Real}

instance + Complex where (+) c1 c2 = {r = c1.r + c2.r, i = c1.i + c2.i}
instance - Complex where (-) c1 c2 = {r = c1.r - c2.r, i = c1.i - c2.i}
instance * Complex where (*) c1 c2 = { r = c1.r * c2.r - c1.i * c2.i
                                     , i = c1.r * c2.i + c1.i * c2.r }

cooley_turkey :: [a] -> [Complex] | toReal a
cooley_turkey data
  | len bitand (len - 1) <> 0
      = abort "data length must be a power of 2\n"
  | otherwise = ditfft2 (map (\x -> {r = toReal x, i = 0.0}) data)
  where
    len = length data
    ditfft2 :: [Complex] -> [Complex]
    ditfft2 ls =
      case length ls of
        0 -> []
        1 -> ls
        n -> let evens = ditfft2(filterByIndex ls (\c -> isEven c)) // see fusion_error.icl
                 odds  = ditfft2(filterByIndex ls (\c -> isOdd c))
                 phase = map (\x -> let p = -2.0 * pi * (toReal x) / (toReal n)
                                    in {r = cos p, i = sin p})
                             [0.. n]
                 ops   = zipWith (*) odds phase
                 one   = zipWith (+) evens ops
                 two   = zipWith (-) evens ops
             in one ++ two

filterByIndex :: [a] (Int -> Bool) -> [a]
filterByIndex ls p = map fst (filter (p o snd) (zip2 ls (indexList ls)))

pi = 3.141592653589

Start = cooley_turkey [1.0, 2.0 .. 1024.0]

// Can't define restricted resynonum types
// ::FFT :== A.a : [a] -> [Complex] | toReal a
