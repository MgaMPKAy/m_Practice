module Monagologie where

plus :: Num a => a -> a -> (a -> t) -> t
plus x y f = f (x + y)

times :: Num a => a -> a -> (a -> t) -> t
times x y f = f (x * y)

less :: Ord a => a -> a -> t -> t -> t
less x y f g = if (x < y) then f else g

factorial :: (Num a, Ord a) => a -> (a -> t) -> t
factorial n k = less n 2 
                (k 1) $
                plus n (-1) $ 
                         \m -> factorial m $ 
                               \f -> times n f k