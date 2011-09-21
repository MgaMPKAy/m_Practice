module Main where

import Data.List(intersperse)
import Control.Monad(when)

nextLine :: String -> String
nextLine [] = []
nextLine [x] = [x]
nextLine [x,y] = if x == y then "+" else "-"
nextLine (x:y:ys) = nextLine [x,y] ++ nextLine (y:ys)

printSymbolicTriangle :: String -> IO ()
printSymbolicTriangle syms =
  printSTIter syms 0 where
    printSTIter syms n = do
      putStrLn $ replicate n ' ' ++  intersperse ' ' syms
      when (length syms > 1) $
        printSTIter (nextLine syms) (n + 1)

main :: IO ()
main =  getLine >>= printSymbolicTriangle

{-
./SymbolicTriangle
+------+------+------+------+
+ - - - - - - + - - - - - - + - - - - - - + - - - - - - +
 - + + + + + - - + + + + + - - + + + + + - - + + + + + -
  - + + + + - + - + + + + - + - + + + + - + - + + + + -
   - + + + - - - - + + + - - - - + + + - - - - + + + -
    - + + - + + + - + + - + + + - + + - + + + - + + -
     - + - - + + - - + - - + + - - + - - + + - - + -
      - - + - + - + - - + - + - + - - + - + - + - -
       + - - - - - - + - - - - - - + - - - - - - +
        - + + + + + - - + + + + + - - + + + + + -
         - + + + + - + - + + + + - + - + + + + -
          - + + + - - - - + + + - - - - + + + -
           - + + - + + + - + + - + + + - + + -
            - + - - + + - - + - - + + - - + -
             - - + - + - + - - + - + - + - -
              + - - - - - - + - - - - - - +
               - + + + + + - - + + + + + -
                - + + + + - + - + + + + -
                 - + + + - - - - + + + -
                  - + + - + + + - + + -
                   - + - - + + - - + -
                    - - + - + - + - -
                     + - - - - - - +
                      - + + + + + -
                       - + + + + -
                        - + + + -
                         - + + -
                          - + -
                           - -
                            +
-}