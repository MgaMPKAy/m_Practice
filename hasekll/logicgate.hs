-- Direct translate form F# version from news.ycombinator.com/item?id=2958634

import Control.Monad

data LogicGate = ON
               | OFF
               | NAND LogicGate LogicGate
               | NOT LogicGate
               | AND LogicGate LogicGate
               | OR LogicGate LogicGate
               | NOR LogicGate LogicGate
               | XOR LogicGate LogicGate
               | XNOR LogicGate LogicGate
               deriving (Show)

evaluate :: LogicGate -> Bool
evaluate input = case input of
  ON -> True
  OFF -> False
  NAND a b -> not ((evaluate a) && (evaluate b))
  NOT a -> not (evaluate a)
  AND a b -> evaluate (NAND a a)
  OR a b -> evaluate (NAND (NOT a) (NOT b))
  NOR a b -> evaluate (NOT (OR a b))
  XOR a b -> evaluate (AND (NAND a b) (OR a b))
  XNOR a b -> evaluate (NOT (XOR a b))

main =
  mapM (putStrLn . show . evaluate) [NAND OFF OFF, NAND OFF ON, NAND ON OFF, NAND ON ON]
