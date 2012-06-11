module Eval (eval) where

import Types
import Data.Maybe (fromJust)

evalProp (PNot p1)    env = not $ evalProp p1 env
evalProp (PAnd p1 p2) env = evalProp p1 env && evalProp p2 env
evalProp (POr  p1 p2) env = evalProp p1 env || evalProp p2 env
evalProp (PVar name)  env = fromJust $ lookup name env

eval = evalProp
