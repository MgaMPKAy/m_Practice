module Main where

import Control.Concurrent

threadA :: QSem -> IO ()
threadA aIsDone = do
    putStrLn $ "Statement A"
    signalQSem aIsDone

threadB :: QSem -> IO ()
threadB aIsDone = do
    waitQSem aIsDone
    putStrLn $ "Statement B"


main :: IO Char
main = do
    aIsDone <- newQSem 0
    forkIO $ threadB aIsDone
    forkIO $ threadA aIsDone
    getChar
           
    