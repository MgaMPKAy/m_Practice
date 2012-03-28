module Main where

import System.IO

compareCount :: Ord a => [(a,a)] -> (Int, Int, Int)
compareCount = flip comp $ (0,0,0)

comp [] (g, l, e)= (g, l, e)
comp [(x,y)] (g, l, e) =
  case compare x y of
    GT -> (g + 1, l, e)
    LT -> (g , l + 1, e)
    EQ -> (g, l, e + 1)
comp (p:ps) count@(g, l, e) =
  comp ps $ comp [p] count

getNumPair = do
  ws <- (\ws ->  return $ words ws) =<< getLine
  let p = map read  ws :: [Int]
  case p of
    [x,y] -> getNumPair >>= (\ps -> return $ (x,y) : ps)
    otherwise -> return $ []

main = getNumPair >>= (\ps -> return $ compareCount ps) >>= print