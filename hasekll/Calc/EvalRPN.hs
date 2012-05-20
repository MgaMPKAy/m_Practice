module EvalRPN (evalRPN) where

import Types
import Data.Map(insert, lookup)
import Prelude hiding (lookup)
import Data.Maybe (fromJust)

evalRPN input env = evalRPN' input ([], env)

evalRPN' [] (output, env) =
    if (length output > 1) then error "evalRPN" else (output, env)
evalRPN' (t:ts) (output, env)
    | isConst t || isVar t = evalRPN' ts ((t : output), env)
    | t == opAdd && tokenNum >= 1     = evalRPN' ts (evalAdd output env)
    | t == opSub && tokenNum >= 2     = evalRPN' ts (evalSub output env)
    | t == opMul && tokenNum >= 2     = evalRPN' ts (evalMul output env)
    | t == opDiv && tokenNum >= 2     = evalRPN' ts (evalDiv output env)
    | t == opNeg && tokenNum >= 1     = evalRPN' ts (evalNeg output env)
    | t == opPow && tokenNum >= 2     = evalRPN' ts (evalPow output env)
    | t == opAssign && tokenNum >= 2  = evalRPN' ts (evalAssign output env)
    | otherwise = error ("evalRPN error: " ++ show (t))
  where
    tokenNum = length output

    evalAdd (o1:o2:os) env = (Const (eval o1 + eval o2) : os, env)
    evalSub (o1:o2:os) env = (Const (eval o2 - eval o1) : os, env)
    evalMul (o1:o2:os) env = (Const (eval o1 * eval o2) : os, env)
    evalDiv (o1:o2:os) env = (Const (eval o2 / eval o1) : os, env)
    evalNeg (o1:os)    env = (Const ((-1) * eval o1) : os, env)
    evalPow (o1:o2:os) env = (Const (eval o2 ** eval o1) : os, env)
    evalAssign (o1:o2:os) env = (o1:os, insert (fromVar o2) (eval o1) env)

    eval (Const x)  = x
    eval (Var name) = fromJust $ lookup name env