module Main where

import Types
import Tokenizer
import Parser
import Eval

import Control.Monad (replicateM, when)
import Data.List (nub, foldl')

main = do
    tokens <- fmap tokenize getLine
    let (varibleNum, varibleNames) = countVarible tokens
        uniqNames = nub varibleNames
        prop = parse tokens
        envs = mkEnvs (length uniqNames) uniqNames
        truths = map (eval prop) envs
    printResult truths
    main

printResult truths =
    if alwaysTrue truths
        then print "True forever"
        else if alwaysFalse truths
                 then print "False forever"
                 else print "Satisfactible"

mkEnvs varibleNum varibleNames =
    let truthTable = replicateM varibleNum [True, False]
    in map (zip varibleNames) truthTable

countVarible token = foldl' step (0, []) token
  where
    step (count, names) token
         | isVar token = (count + 1, ((\(Var x) -> x) token) :  names)
         | otherwise   = (count, names)

alwaysTrue = and

alwaysFalse = all (False ==)
