module Tokenizer
    (
     tokenize
    )
where

import Types

tokenize :: String -> [Token]
tokenize input = reverse $ End : tokenize' input [] []

tokenize' [] varAcc tokens =
    if null varAcc
        then tokens
        else (Var $ reverse $ varAcc) : tokens
tokenize' (x:xs) varAcc tokens
    | x `elem` whitespaces = if null varAcc
                                 then tokenize' xs varAcc tokens
                                 else tokenize' xs [] (varible :  tokens)
    | x `elem` alphabet    = tokenize' xs (x : varAcc) tokens
    | x == '('             = addTokenLoop LeftParen
    | x == ')'             = addTokenLoop RightParen
    | x == '&'             = addTokenLoop OpAnd
    | x == '~'             = addTokenLoop OpNot
    | x == '|'             = addTokenLoop OpOr
    | otherwise            = error "illegal input"
  where
    addTokenLoop token
        | null varAcc = tokenize' xs [] (token : tokens)
        | otherwise   = tokenize' xs [] (token : varible : tokens)

    varible = Var $ reverse $ varAcc

whitespaces = ['\n', '\t', '\r', ' ']
alphabet = ['a'..'z'] ++ ['A'..'Z']
