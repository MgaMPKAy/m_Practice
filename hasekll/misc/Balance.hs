module Balance where

import Stack

isBalance :: String -> Bool
isBalance str = isBalanceS str newStack
  where 
    isBalanceS str s
        | null str && isEmpty s = True
        | null str = False
        | (head str) `elem` ['(', '{', '['] = 
            isBalanceS (tail str) (push (head str) s)
        | (head str) == ')' = match '(' str s
        | (head str) == ']' = match '[' str s
        | (head str) == '}' = match '{' str s
        | otherwise = isBalanceS (tail str) s
    match c str s = 
        if (isEmpty s || fst (pop s) /= c)
            then False
            else isBalanceS (tail str) (snd $ pop s)

-- evaluate :: String -> Stack Char -> Stack Double -> Double