module StraightLineProgram where

import Data.Maybe (fromJust)
import Data.Map(Map, insert, lookup, empty)
import Prelude hiding (lookup)

data Stm
    = CompoundStm Stm Stm
    | AssignStm String Exp
    | PrintStm ExpList
    deriving (Show)

data Exp
    = IdExp String
    | NumExp Double
    | OpExp Exp BinOP Exp
    | EseqExp Stm Exp
    deriving (Show)

data ExpList
    = PairExpList Exp ExpList
    | LastExpList Exp
    deriving (Show)

data BinOP = Plus | Minus | Times | Div deriving (Show)

maxArgs :: Stm -> Int
maxArgs (CompoundStm stm1 stm2) = max (maxArgs stm1) (maxArgs stm2)
maxArgs (AssignStm _ exp1) = maxArgsExp exp1
maxArgs (PrintStm explist) = maxArgsExpList explist

maxArgsExp :: Exp -> Int
maxArgsExp (IdExp _) = 0
maxArgsExp (NumExp _) = 0
maxArgsExp (OpExp exp1 _ exp2) = max (maxArgsExp exp1) (maxArgsExp exp2)
maxArgsExp (EseqExp stm exp1) = max (maxArgs stm) (maxArgsExp exp1)

maxArgsExpList el = maxArgsExpList' el (expListLength el)

maxArgsExpList' el@(PairExpList (EseqExp stm exp) expList) maxLen =
    maximum [maxArgs stm, maxArgsExp exp, maxArgsExpList expList, maxLen]
maxArgsExpList' el@(LastExpList (EseqExp stm exp)) maxLen =
    maximum [maxArgs stm, maxArgsExp exp, maxLen]
maxArgsExpList' el maxlen = maxlen

expListLength (LastExpList _) = 1
expListLength (PairExpList _ el) = 1 + expListLength el


type Env = Map String Double
type Result = String

interpStm :: Stm -> (Env, Result) -> (Env, Result)
interpStm (CompoundStm stm1 stm2) (env, result) =
    interpStm stm2 (interpStm stm1 (env, result))
interpStm (AssignStm varName exp) (env, result) =
    let (num, env1, result1) = interpExp exp (env, result)
    in (insert varName num env1, result)
interpStm (PrintStm expList ) (env, result) =
    interpExpList expList (env, result)

interpExp (NumExp num) (env, result) = (num, env, result)
interpExp (IdExp varName) (env, result) =
    (fromJust $ lookup varName env, env, result)
interpExp (EseqExp stm exp) (env, result) =
    let (env1, result1) = interpStm stm (env, result)
    in interpExp exp (env1, result1)
interpExp (OpExp exp1 op exp2) (env, result) =
    let (num1, env1, result1) = interpExp exp1 (env, result)
        (num2, env2, result2) = interpExp exp2 (env1, result1)
        num = case op of
                Plus  -> num1 + num2
                Minus -> num1 - num2
                Times -> num1 * num2
                Div   -> num1 / num2
    in (num, env2, result2)


interpExpList (PairExpList exp explist) (env, result) =
    let (num, env1, result1) = interpExp exp (env, result)
    in interpExpList explist (env1, result1 ++ show num ++ "\n")

interpExpList (LastExpList exp) (env, result) =
    let (num, env1, result1) = interpExp exp (env, result)
    in (env1, result1 ++ show num ++ "\n")

interp stm = putStr $ snd $ interpStm stm (empty, [])


-- test data

prog :: Stm
prog = CompoundStm
       (AssignStm "a" (OpExp (NumExp 5) Plus (NumExp 3)))
       (CompoundStm
        (AssignStm "b"
         (EseqExp
          (PrintStm
           (PairExpList
            (IdExp "a")
            (LastExpList (OpExp (IdExp "a") Minus (NumExp 1)))))
          (OpExp (NumExp 10) Times (IdExp "a"))))
        (PrintStm (LastExpList (IdExp "b"))))


print1 = PrintStm (LastExpList (NumExp 1))

print2 = (PrintStm
           (PairExpList (NumExp 1)
            (LastExpList (NumExp 2))))

print3 = (PrintStm
          (PairExpList (NumExp 1)
           (PairExpList (NumExp 2)
            (LastExpList (NumExp 3)))))

print2' = (PrintStm
           (PairExpList (EseqExp print1 (NumExp 1))
            (LastExpList (NumExp 1))))

print4 = (PrintStm
           (PairExpList (EseqExp print2 (NumExp 1))
            (PairExpList (NumExp 2)
             (PairExpList (NumExp 4)
              (LastExpList (NumExp 2))))))

print6' = (PrintStm
           (PairExpList (EseqExp print2 (NumExp 1))
              (PairExpList (EseqExp print4 (NumExp 1))
               (LastExpList (EseqExp print6 (NumExp 1))))))

print6 = (PrintStm
           (PairExpList (EseqExp print2 (NumExp 1))
            (PairExpList (EseqExp print4 (NumExp 1))
             (PairExpList (EseqExp print4 (NumExp 1))
              (PairExpList (EseqExp print4 (NumExp 1))
               (PairExpList (EseqExp print4 (NumExp 1))
                (LastExpList (NumExp 2))))))))
