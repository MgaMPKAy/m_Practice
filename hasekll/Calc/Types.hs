module Types
    (
      Token(..)
    , Associativity(..)
    , Name
    , Precedence
    , isOperator, isConst
    , opAdd, opSub, opMul, opDiv, opNeg
    )
where

data Token = Const Double
           | LeftParen
           | RightParen
           | Operator {
               unName  :: Name
             , unPred  :: Precedence
             , unAssoc :: Associativity
             }
             deriving (Show, Eq)

type Name = String
type Precedence = Int

data Associativity = LeftAssoc | RightAssoc deriving (Show, Eq)

isOperator (Operator _ _ _) = True
isOperator _ = False

isConst (Const _) = True
isConst _ = False

opAdd = Operator "+" 1 LeftAssoc
opSub = Operator "-" 1 LeftAssoc
opMul = Operator "*" 2 LeftAssoc
opDiv = Operator "/" 2 LeftAssoc
opNeg = Operator "-" 3 LeftAssoc
