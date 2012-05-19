module Tokenizer (tokenize) where

import Types

tokenize :: String -> [Token]
tokenize input = reverse $ tokenize' input [] []

tokenize' [] varAcc tokens =
    if null varAcc
        then tokens
        else (Const $ read $ reverse $ varAcc) : tokens
tokenize' (x:xs) varAcc tokens
    | x `elem` whitespaces = if null varAcc
                                 then tokenize' xs varAcc tokens
                                 else tokenize' xs [] (varible :  tokens)
    | x `elem` nums        = tokenize' xs (x : varAcc) tokens
    | x == '-' && isNeg    = addTokenLoop opNeg
    | x == '('             = addTokenLoop LeftParen
    | x == ')'             = addTokenLoop RightParen
    | x == '+'             = addTokenLoop opAdd
    | x == '-'             = addTokenLoop opSub
    | x == '*'             = addTokenLoop opMul
    | x == '/'             = addTokenLoop opDiv
    | otherwise            = error "illegal input"
  where
    addTokenLoop token
        | null varAcc = tokenize' xs [] (token : tokens)
        | otherwise   = tokenize' xs [] (token : varible : tokens)

    varible = Const $ read $ reverse $ varAcc

    isNeg = (null tokens && null varAcc)
            || ((not (null tokens) && null varAcc)
                && (isOperator (head tokens) || head tokens == LeftParen))

whitespaces = ['\n', '\t', '\r', ' ']
nums = ['0'..'9']