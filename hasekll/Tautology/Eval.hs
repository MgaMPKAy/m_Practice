module Eval (eval) where

import Types
import Data.Maybe (fromJust)

evalTerm (TVar name) env = fromJust $ lookup name env
evalTerm (TParen prop) env = evalProp prop env
evalTerm (TNot prop) env = not $ evalProp prop env

evalExp (ETerm term) env = evalTerm term env
evalExp (EAnd term exp) env = evalExp exp env && evalTerm term env

evalProp (PExp exp) env = evalExp exp env
evalProp (POr exp prop) env = evalExp exp env || evalProp prop env

eval = evalProp
