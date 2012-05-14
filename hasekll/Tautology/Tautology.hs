module Main where

import Types
import Tokenizer
import ToRPN
import EvalRPN
import Tests

import Control.Monad (replicateM, when)
import Data.List (nub, foldl')
import Control.Applicative

main = do
    rpn <- fmap (toRPN . tokenize) getLine
    let (varibleNum, varibleNames) = countVarible rpn
        envs = mkEnvs varibleNum (nub varibleNames)
        truths = map (evalRPN rpn) envs
    when (alwaysTrue truths) (print "True forever")
    when (alwaysFalse truths) (print "False forever")
    when (or truths) (print "Satisfactible")
    main

mkEnvs varibleNum varibleNames =
    let truthTable = replicateM varibleNum [True, False]
    in map (zip varibleNames) truthTable

countVarible token = foldl' step (0, []) token
  where
    step (count, names) token
         | isVar token = (count + 1, ((\(Var x) -> x) token) :  names)
         | otherwise   = (count, names)

alwaysTrue = and

alwaysFalse = not . or