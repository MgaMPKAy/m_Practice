module Coroutine where

import Control.Applicative
import Control.Arrow
import Control.Category
import Prelude hiding (id, (.))

data Stream1 a = Stream1 a (Stream1 a)

intsFrom1 :: Int -> Stream1 Int
intsFrom1 n = Stream1 n $ intsFrom1 (n + 1)

data Stream2 a = Stream2(() -> (a, Stream2 a))

intsFrom2 :: Int -> Stream2 Int
intsFrom2 n = Stream2 (\() -> (n, intsFrom2 (n + 1)))


data Stream b a = Stream (b -> (a, Stream b a))

newtype Coroutine i o = Coroutine {
      runC :: i -> (o, Coroutine i o)
}

instance Functor (Coroutine i) where
    fmap f co = Coroutine $ \i ->
                let (o, co') = runC co i
                in (f o, fmap f co')

instance Applicative (Coroutine i) where
    pure x = Coroutine $ const (x, pure x)
             
    cof <*> cox = Coroutine $ \i ->
                  let (f, cof') = runC cof i
                      (x, cox') = runC cox i
                  in (f x, cof' <*> cox')

evalList :: Coroutine i o -> [i] -> [o]
evalList _ [] = []
evalList co (x:xs) = o : evalList co' xs
  where (o, co') = runC co x

intsFrom ::  Int -> Coroutine () Int
intsFrom n = Coroutine $ \_ -> (n, intsFrom (n + 1))

instance  Category Coroutine where
    id = Coroutine $ \i -> (i, id)
    
    cof . cog = Coroutine $ \i ->
                let (x, cog') = runC cog i 
                    (y, cof') = runC cof x
                in (y, cof' . cog')