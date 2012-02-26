{-# LANGUAGE TypeSynonymInstances, FlexibleInstances #-}
module NumChar where

import Data.Char

instance Num Char where
    a + b = undefined
    a - b = undefined
    a * b = undefined
    abs = undefined
    signum = undefined
    fromInteger x = chr (fromInteger x)
