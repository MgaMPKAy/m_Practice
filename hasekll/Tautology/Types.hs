module Types
    (
      Token(..)
    , Associativity(..)
    , Name
    , Precedence
    , isOperator, isVar, isConst
    , opNot, opAnd, opOr,
    )
where

data Token = Var Name
           | Const Bool
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

isVar (Var _) = True
isVar _ = False

isConst (Const _) = True
isConst _ = False

opOr  = Operator "|" 1 LeftAssoc
opAnd = Operator "&" 2 LeftAssoc
opNot = Operator "~" 3 RightAssoc

