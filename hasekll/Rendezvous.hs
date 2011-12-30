module Main where

import Control.Concurrent

threadA :: QSem -> QSem -> IO ()
threadA a1done b1done = do
    putStrLn "Statement A1"
    signalQSem a1done
    waitQSem b1done
    putStrLn "Statement A2"
    

threadB :: QSem -> QSem -> IO ()
threadB a1done b1done = do
    putStrLn "Statement B1"
    signalQSem b1done
    waitQSem a1done
    putStrLn "Statement B2"


main :: IO Char
main = do
    a1done <- newQSem 0
    b1done <- newQSem 0
    forkIO $ threadA a1done b1done
    forkIO $ threadB a1done b1done
    getChar
           
    