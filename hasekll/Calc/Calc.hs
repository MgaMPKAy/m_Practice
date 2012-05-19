module Main where

import Tokenizer (tokenize)
import ToRPN (toRPN)
import EvalRPN (evalRPN)

main = do
    getLine
    >>= return . evalRPN . toRPN . tokenize
    >>= print
    >> main