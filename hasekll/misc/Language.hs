module Language where

import Data.List

data Expr a = EVar Name
            | ENum Int
            | EConster Int Int
            | EAp (Expr a) (Expr a)
            | ELet IsRec [(a, Expr a)] (Expr a)
            | ECase (Expr a) [Alter a]
            | Elam [a] (Expr a)
              deriving (Show)

type CoreExpr = Expr Name
type Name = String

type IsRec   = Bool
recursive, nonrecursive :: IsRec
recursive    = True
nonrecursive = False


bindersOf :: [(a, b)] -> [a]
bindersOf defns = [name | (name, _) <- defns]

rhssOf :: [(a, b)] -> [b]
rhssOf defns    = [rhs | (_, rhs) <- defns]

type Alter a = (Int, [a], Expr a)
type CoreAlt = Alter Name

isAtomicExpr :: Expr a -> Bool
isAtomicExpr (EVar _) = True
isAtomicExpr (ENum _) = True
isAtomicExpr _        = False

type Program a = [ScDefn a]
type CoreProgram = Program Name

type ScDefn a = (Name, [a], Expr a)
type CoreScDefn = ScDefn Name

{-
main = double 21;
double x = x + x
[("main", [], (EAp (EVar "double") (ENum 21))),
 ("double", ["x"], (EAp (EAp (EVar "+") (EVar "x")) (EVar "x")))
]
-}

preludeDefs :: CoreProgram
preludeDefs =
    [("I", ["x"], EVar "x"),
     ("K", ["x", "y"], EVar "x"),
     ("K1", ["x", "y"], EVar "y"),
     ("S", ["f", "g", "x"], EAp (EAp (EVar "f") (EVar "x"))
                                (EAp (EVar "g") (EVar "x"))),
     ("compose", ["f", "g", "x"], EAp (EVar "f")
                                      (EAp (EVar "g") (EVar "x"))),
     ("twice", ["f"], EAp (EAp (EVar "compose") (EVar "f")) (EVar "f"))
     ]
      
-- pprint :: CoreProgram -> String

pprExpr :: Expr a -> String
pprExpr (ENum n) = show n
pprExpr (EVar v) = v
pprExpr (EAp e1 e2) = pprExpr e1 ++ " " ++ pprAExpr e2

pprAExpr e
    | isAtomicExpr e = pprExpr e
    | otherwise = "(" ++ pprExpr e ++ ")"

mkMultiAp :: Int -> CoreExpr -> CoreExpr -> CoreExpr
mkMultiAp n e1 e2 = foldl EAp e1 (take n e2s)
    where e2s = e2 : e2s