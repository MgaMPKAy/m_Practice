module EvalRPN
    (
      evalRPN
    )
where

import Types
import Data.Maybe (fromJust)

evalRPN input env = (\(Const x) -> x) $ head (evalRPN' input [] env)

evalRPN' [] output env = if (length output > 1) then error "evalRPN" else output
evalRPN' (t:ts) output env
    | isVar t = evalRPN' ts (Const (eval t) : output) env
    | t == opNot && varibleNum >= 1 = evalRPN' ts (evalNot output) env
    | t == opOr  && varibleNum >= 2 = evalRPN' ts (evalOr  output) env
    | t == opAnd && varibleNum >= 2 = evalRPN' ts (evalAnd output) env
    | otherwise = error (show (t:ts, output))
  where
    varibleNum = length output
    errMsg     = "No enought varible"

    evalOr  (o1:o2:os)  = Const (eval o1 || eval o2) : os
    evalAnd (o1:o2:os)  = Const (eval o1 && eval o2) : os
    evalNot (o1:os)     = Const (not $ eval o1) : os

    eval (Var name) = fromJust (lookup name env)
    eval (Const x)  = x
