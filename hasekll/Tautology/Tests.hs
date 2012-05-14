module Tests where

import ToRPN
import Tokenizer
import Types
import EvalRPN

-- test1 : 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3
opAdd = Operator "+" 2 LeftAssoc
opSub = Operator "-" 2 LeftAssoc
opMul = Operator "*" 3 LeftAssoc
opDiv = Operator "/" 3 LeftAssoc
opPow = Operator "^" 4 RightAssoc

testTokens1 :: [Token]
testTokens1 = [ Var "3", opAdd, Var "4", opMul, Var "2", opDiv
             , LeftParen, Var "1", opSub, Var "5", RightParen
             , opPow, Var "2", opPow, Var "3"
             ]
test1 = concatMap show (toRPN testTokens1) == "342*15-23^^/+"

-- test2 : ~A & ~B | ~(C & ~D)

var = Var

testTokens2 :: [Token]
testTokens2 = [ opNot, var "A", opAnd, opNot, var "B"
              , opOr, opNot, LeftParen, var "C"
              , opAnd, opNot, var "D", RightParen
              ]


test2 = concatMap show (toRPN testTokens2) == "A~B~&CD~&~|"


testString = " ~A & ~B | ~(C & ~D)"

test3 = concatMap show (toRPN $ tokenize testString) == "A~B~&CD~&~|"

testEnv = [ ("A", False)
          , ("B", False)
          , ("C", False)
          , ("D", True)
          ]

test4 = evalRPN (toRPN $ tokenize$ testString) testEnv

prettyShow (Var name)          = name
prettyShow (Const x)           = show x
prettyShow (Operator name _ _) = name
prettyShow LeftParen           = "("
prettyShow RightParen          = ")"
