module Random where

import System.Random
import Data.List

type Seed = StdGen

-- randomNext :: Seed -> Seed
-- randomNext rand = if newRand > 0
--                       then newRand
--                       else newRand + 214748123
--   where newRand = 15910 * lo - 1339 * hi
--         (hi, lo) = rand `divMod` 12772

-- toDieRoll :: Seed -> Int
-- toDieRoll seed = (seed `mod` 6) + 1

rollDie :: Seed -> (Int, Seed)
rollDie seed = ((rand `mod` 6) + 1, newSeed)
    where (rand, newSeed) = random seed

sumTwoDice :: Seed -> (Int, Seed)
sumTwoDice seed0 = (die1 + die2, seed2)
  where (die1, seed1) = rollDie seed0
        (die2, seed2) = rollDie seed1

rollNDice :: Int -> Seed -> ([Int], Seed)
rollNDice 0 seed = ([], seed)
rollNDice n seed = (dieN : dies, seedN)
  where (dies, seed1) = rollNDice (n - 1) seed
        (dieN, seedN) = rollDie seed1


stat :: (Fractional t, Ord a) => [a] -> [(a, t)]
stat xs = map s (group $ sort xs)
  where s l = (head l,
               fromIntegral (length l) / fromIntegral total)
        total = length xs
