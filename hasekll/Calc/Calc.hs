module Main where

import Types
import Tokenizer (tokenize)
import ToRPN (toRPN)
import EvalRPN (evalRPN)
import Data.Map (empty)

main = do
    loop empty

loop env = do
    input <- getLine
    let tokens = toRPN $ tokenize input
        (result, env') = evalRPN tokens env
    print result
    loop env'
