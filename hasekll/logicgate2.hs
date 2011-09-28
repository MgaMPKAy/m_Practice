module Logic where

import Prelude hiding(and, or, not)
data Signal = T | F deriving(Eq, Read)

instance Show Signal where
    show T = "1"
    show F = "0"

and :: Signal -> Signal -> Signal
and x y = if x == F then F else y
          
or :: Signal -> Signal -> Signal
or x y = if x == T then T else y

not :: Signal -> Signal
not x = if x == T then F else T

xor :: Signal -> Signal -> Signal
xor x y = or (and (not x) y) (and x  (not y))

orl :: [Signal] -> Signal
orl [] = error "orl : arg error"
orl [x] = x
orl [x,y] = or x y
orl (x:xs) = if x == T then T else orl xs

andl :: [Signal] -> Signal
andl [] = error "andl : arg error"
andl [x] = x
andl (x:xs) = if x == F then F else andl xs

xorl :: [Signal] -> Signal
xorl [] = error "xorl : arg error"
xorl [x] = x
xorl [x, y] = xor x y
xorl (x:y:ys) = xorl $ xor x y : ys

gate :: [Signal] -> Signal
gate [a,b,c,d] = 
    orl [andl [a, not $ andl [b,c,d]],
         and (not a) b,
         not (andl [a,b,d]),
         and b (not c),
         andl [b,c,d]]

table :: [(Signal, Signal, Signal, Signal, Signal)]
table = [(a,b,c,d,y) | a <- [F, T], b <- [F, T],
                       c <- [F, T], d <- [F, T], 
                       let y = gate [a, b, c, d]]
