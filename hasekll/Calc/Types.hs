module Types
    (
      Token(..)
    , Associativity(..)
    , Name
    , Precedence
    , isOperator, isConst, isVar
    , fromConst, fromVar
    , opAdd, opSub, opMul, opDiv, opNeg, opAssign, opPow
    )
where

data Token = Var Name
           | Const Double
           | LeftParen
           | RightParen
           | Operator {
               unName  :: Name
             , unPred  :: Precedence
             , unAssoc :: Associativity
             }
             deriving (Eq)

instance Show Token where
    show (Var name) = name
    show (Const num) = show num
    show LeftParen   = "("
    show RightParen  = ")"
    show (Operator name pre _) = name ++ ":" ++ show pre

type Name = String
type Precedence = Int

data Associativity = None | LeftAssoc | RightAssoc deriving (Show, Eq)

isVar (Var _) = True
isVar _ = False

isOperator (Operator _ _ _) = True
isOperator _ = False

isConst (Const _) = True
isConst _ = False

fromVar (Var x) = x
fromConst (Const x) = x

opAssign = Operator "=" 0 RightAssoc
opAdd = Operator "+" 1 LeftAssoc
opSub = Operator "-" 1 LeftAssoc
opNeg = Operator "-" 2 None
opMul = Operator "*" 3 LeftAssoc
opDiv = Operator "/" 3 LeftAssoc
opPow = Operator "^" 4 RightAssoc