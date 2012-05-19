module Types
    (
      Token(..)
    , Associativity(..)
    , Name
    , Precedence
    , isOperator, isConst, isVar
    , opAdd, opSub, opMul, opDiv, opNeg, opAssign
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
    show (Operator name _ _) = name

type Name = String
type Precedence = Int

data Associativity = LeftAssoc | RightAssoc deriving (Show, Eq)

isVar (Var _) = True
isVar _ = False

isOperator (Operator _ _ _) = True
isOperator _ = False

isConst (Const _) = True
isConst _ = False

opAssign = Operator "=" 0 RightAssoc
opAdd = Operator "+" 1 LeftAssoc
opSub = Operator "-" 1 LeftAssoc
opMul = Operator "*" 2 LeftAssoc
opDiv = Operator "/" 2 LeftAssoc
opNeg = Operator "-" 3 LeftAssoc
