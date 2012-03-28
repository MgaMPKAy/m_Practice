module Foldr where

dropWhile' :: (a -> Bool) -> [a] -> [a]
dropWhile' _ [] = []
dropWhile' p l@(x:xs)
    | p x = dropWhile' p xs
    | otherwise = l

{-- Trial 1
myDropWhile :: (a -> Bool) -> [a] -> [a]
myDropWhile p l = fst $ foldr step ([], False) l
  where
    step x (acc, s)
         | s = (x:acc, s)
         | p x = (acc, False)
         | otherwise = (x:acc, True)

myDropWhile' :: (b -> Bool) -> [b] -> [b]
myDropWhile' p l = reverse $ fst $ foldl step ([], False) l
  where
    step (acc, s) x
         | s = (x:acc, s)
         | p x = (acc, False)
         | otherwise = (x:acc, True)

Use foldr to implement foldl
foldr :: (a -> b -> b) -> b -> [a] -> b
foldl :: (a -> b -> a) -> a -> [b] -> a
--}