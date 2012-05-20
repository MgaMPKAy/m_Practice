module Tokenizer (tokenize) where

import Types

tokenize :: String -> [Token]
tokenize input = reverse $ tokenize' input []

tokenize' [] tokens = tokens
tokenize' (x:xs) tokens
    | x `elem` whitespaces = tokenize' xs tokens
    | x `elem` digits      = let (tokConst, input) = getConst (x:xs)
                             in tokenize' input (tokConst : tokens)
    | x `elem` alphabet    = let (tokVar, input) = getVar (x:xs)
                             in tokenize' input (tokVar : tokens)
    | x == '-' && isNeg    = addTokenLoop opNeg
    | x == '('             = addTokenLoop LeftParen
    | x == ')'             = addTokenLoop RightParen
    | x == '+'             = addTokenLoop opAdd
    | x == '-'             = addTokenLoop opSub
    | x == '*'             = addTokenLoop opMul
    | x == '/'             = addTokenLoop opDiv
    | x == '='             = addTokenLoop opAssign
    | x == '^'             = addTokenLoop opPow
    | otherwise            = error "illegal input"
  where
    addTokenLoop token = tokenize' xs (token : tokens)

    isNeg = null tokens
            || (isOperator (head tokens) || head tokens == LeftParen)

whitespaces = ['\n', '\t', '\r', ' ']
digits = ['0'..'9'] ++ "e."
alphabet = ['A'..'Z'] ++ ['a'..'z']

getVar input =
    let tokVar = Var $ takeWhile (`elem` alphabet) input
        input' = dropWhile (`elem` alphabet) input
    in (tokVar, input')

getConst input =
    let tokConst = Const $ read $ takeWhile (`elem` digits) input
        input' = dropWhile (`elem` digits) input
    in (tokConst, input')
