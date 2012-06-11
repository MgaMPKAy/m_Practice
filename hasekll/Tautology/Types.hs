module Types
    (
      Token(..)
    , Prop (..)
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
             deriving (Show, Eq)

data Prop = PAnd Prop Prop
          | POr Prop Prop
          | PNot Prop
          | PVar Name
            deriving (Show, Eq)

type Name = String

isOperator t = t `elem` [OpNot, OpAnd, OpOr]

isVar (Var _) = True
isVar _ = False

isConst (Const _) = True
isConst _ = False
