module Types
    (
      Token(..)
    , Prop (..)
    , Exp  (..)
    , Term (..)
    , Name
    , isOperator, isVar, isConst
    )
where

data Token = Var Name
           | Const Bool
           | LeftParen
           | RightParen
           | OpNot
           | OpAnd
           | OpOr
           | End
             deriving (Eq)

data Prop = PExp Exp
          | POr Exp Prop
            deriving (Eq)

data Exp = ETerm Term
         | EAnd Term Exp
           deriving (Eq)

data Term = TVar Name
          | TParen Prop
          | TNot Prop
            deriving (Eq)

type Name = String

isOperator t = t `elem` [OpNot, OpAnd, OpOr]

isVar (Var _) = True
isVar _ = False

isConst (Const _) = True
isConst _ = False
