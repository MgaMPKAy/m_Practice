module EvalRPN (evalRPN) where

import Types

evalRPN input = (\(Const x) -> x) $ head (evalRPN' input [])

evalRPN' [] output =
    if (length output > 1) then error "evalRPN" else output
evalRPN' (t:ts) output
    | isConst t = evalRPN' ts (t : output)
    | t == opAdd && varibleNum >= 1 = evalRPN' ts (evalAdd output)
    | t == opSub && varibleNum >= 2 = evalRPN' ts (evalSub output)
    | t == opMul && varibleNum >= 2 = evalRPN' ts (evalMul output)
    | t == opDiv && varibleNum >= 2 = evalRPN' ts (evalDiv output)
    | t == opNeg && varibleNum >= 1 = evalRPN' ts (evalNeg output)
    | otherwise = error ("evalRPN: x " ++ show (t:ts, output))
  where
    varibleNum = length output

    evalAdd (o1:o2:os)  = Const (eval o1 + eval o2) : os
    evalSub (o1:o2:os)  = Const (eval o2 - eval o1) : os
    evalMul (o1:o2:os)  = Const (eval o1 * eval o2) : os
    evalDiv (o1:o2:os)  = Const (eval o2 / eval o1) : os
    evalNeg (o1:os)     = Const ((-1) * eval o1) : os

    eval (Const x)  = x
