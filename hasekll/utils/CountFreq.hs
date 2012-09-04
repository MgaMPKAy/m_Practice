module Main where

import Data.List (sort, group)

countFreq l = sort $ map (\x -> (length x, concat $ head x)) $ group $ sort $ map (take 1) $ map words $ lines l

(|>) = flip ($)

countFreq2 l =
    l |> lines
      |> map words
      |> map (take 1)
      |> sort
      |> group
      |> map (\x -> (length x, concat $ head x))
      |> sort


main = readFile "bash_history" >>= (mapM_ print) . countFreq2