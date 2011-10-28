{-# LANGUAGE NoMonomorphismRestriction  #-}

import Diagrams.Prelude
import Diagrams.Backend.Cairo.CmdLine

main = defaultMain $ 
       square 1 # fc aqua `atop` (circle1 ||| circle2)
       === (circle 1)
       === beside (10,10) (square 1 # fc yellow )  (square 1 # fc black)
       === (ell ||| ell)

circle1 = circle 1 
          # fc blue
          # lw 0.05
          # lc purple
          # dashing [0.2, 0.05] 0
          # pad 1.1 

circle2 = circle 1 # fc green # lw 0 # showOrigin

ell = circle 1 # scaleX 0.5 # rotateBy (1/6)