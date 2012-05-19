module Main where

import Types
import Tokenizer (tokenize)
import ToRPN (toRPN)
import EvalRPN (evalRPN)
import Data.Map (empty)

main = do
    loop empty
  where
    loop env = do
        input <- getLine
        if input == "p"
            then do
                print env
                loop env
            else do
                let tokens = toRPN $ tokenize input
                let (result, env') = evalRPN tokens env
                if null result
                    then do
                        loop env'
                   else do
                       print (head result)
                       loop env'
