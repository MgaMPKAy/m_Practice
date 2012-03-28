module Pattern where

import Prelude hiding (scanl)

scanl :: (a -> b -> a) -> a -> [b] -> [a]
scanl _ s []     = [s]
scanl f s (x:xs) = s : scanl f (f s x) xs

inits :: [b] -> [[b]]
inits = scanl snoc [] where snoc x a = x ++ [a]

scanl' :: (a -> b -> a) -> a -> [b] -> [a]
scanl' f e = map (foldl f e) . inits


