module Main where

import Data.List(delete)

data Expr = Add Expr Expr
          | Sub Expr Expr
          | Mul Expr Expr
          | Div Expr Expr
          | Var Float
            deriving (Show, Eq)

eval (Var n) = n
eval (Add e1 e2) = eval e1 + eval e2
eval (Sub e1 e2) = eval e1 - eval e2
eval (Mul e1 e2) = eval e1 * eval e2
eval (Div e1 e2) = eval e1 / eval e2

pat1 op1 op2 op3 n1 n2 n3 n4 = op1 (Var n1) (op2 (Var n2) (op3 (Var n3) (Var n4)))
pat2 op1 op2 op3 n1 n2 n3 n4 = op1 (op2 (Var n1) (Var n2)) (op3 (Var n3) (Var n4))

ops = [Add, Sub, Mul, Div]

result nums =
    [ if (abs (eval (pat1 op1 op2 op3 n1 n2 n3 n4) - 24) < 0.001)
         then pat1 op1 op2 op3 n1 n2 n3 n4
         else pat2 op1 op2 op3 n1 n2 n3 n4
     | op1 <- ops
     , op2 <- ops
     , op3 <- ops
     , n1  <- nums
     , n2  <- delete n1 nums
     , n3  <- delete n2 (delete n1 nums)
     , n4  <- delete n3 (delete n2 (delete n1 nums))
     , abs (eval (pat1 op1 op2 op3 n1 n2 n3 n4) - 24) < 0.001
       || abs (eval (pat2 op1 op2 op3 n1 n2 n3 n4) - 24) < 0.001
    ]


main = mapM_ print $ result [3, 4, 6,8]

