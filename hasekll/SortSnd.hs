import Data.List
import Data.Function

sortSnd :: Ord b => [(a, b)] -> [(a, b)]
sortSnd = sortBy (compare `on` snd)

sortSnd' :: Ord b => [(a, b)] -> [(a, b)]
sortSnd' = swap . sort . swap
  where
    swap = map (\(a,b) -> (b, a))

 main = print $ sortSnd [(1,2), (2,1), (3,0)]