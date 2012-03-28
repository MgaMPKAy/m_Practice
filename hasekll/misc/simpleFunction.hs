module Main where

import Control.Monad

func :: Integer -> Integer
func 0 = 1
func n = n * func (n `div` 2)

func' :: Integer -> Integer
func' n =
  funcIter n 1 where
    funcIter n acc
      | n == 0 = acc
      | otherwise = funcIter (n `div` 2) (n * acc)