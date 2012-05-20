module ToRPN (toRPN) where

import Types
import Data.Ord (comparing)

toRPN :: [Token] -> [Token]
toRPN tokens = reverse $ toRPN' tokens [] []
  where
    toRPN' [] stack output = popAll stack output
    toRPN' toekns@(t:ts) stack output =
        case t of
          Var _          -> toRPN' ts stack (t : output)
          Const _        -> toRPN' ts stack (t : output)
          LeftParen      -> toRPN' ts (t : stack) output
          RightParen     -> let (stack', output')
                                    = popUntilLeftParen stack output
                            in toRPN' ts stack' output'
          Operator _ _ _ -> let (stack', output')
                                    = popOperator t stack output
                            in toRPN' ts (t : stack') output'

    popAll [] output = output
    popAll tokens@(t:ts) output =
        case t of
          Operator _ _ _ -> popAll ts (t : output)
          illegalToken   -> error "illegal token lefted in stack"

    popUntilLeftParen [] output = error "paren not match"
    popUntilLeftParen (top:xs) output =
        case top of
          LeftParen -> (xs, output)
          token     -> popUntilLeftParen xs (top : output)

    popOperator op [] output = ([], output)
    popOperator op stack@(top:xs) output
        | isOperator top && shouldPop = popOperator op xs (top : output)
        | otherwise                   = (stack, output)
      where
        shouldPop
            -- if current operator(op) is unary, don't pop stack
            | unAssoc op == None = False
            -- if top of stack is unary
            -- pop only if op's precedence < top's (TODO: < or <=)
            | unAssoc top == None && assocCompare == LT = True
            -- neighter top or currnt operator is unary
            -- pop if top is left  assoc and op's precedence <= top's
            -- or     top is right assoc and op's precedence == top's
            | otherwise =
                or [ unAssoc top == LeftAssoc  && assocCompare /= GT
                   , unAssoc top == RightAssoc && assocCompare == LT
                   ]
        assocCompare = comparing unPred op top