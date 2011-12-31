module Main where

import Control.Concurrent
import Control.Monad
import Data.IORef

totalThread :: Int
totalThread = 5

thread :: IORef Int -> QSem -> QSem -> QSem -> Int -> Int -> IO b
thread count mutex b1 b2 time n = do
    myThreadId >>= (\tid -> putStrLn $ show tid ++ "\t" ++ show n ++ "\tRend")
        
    waitQSem mutex
    modifyIORef count (+1)
    c1 <- readIORef count
    when (c1 == totalThread) $ do
            waitQSem b2
            signalQSem b1
    signalQSem mutex

    waitQSem b1
    signalQSem b1

    myThreadId >>= (\tid -> putStrLn $ show tid ++ "\t" ++ show n ++ "\tCritic")

    waitQSem mutex
    modifyIORef count (subtract 1)
    c2 <- readIORef count
    when (c2 == 0) $ do
            waitQSem b1
            signalQSem b2
    signalQSem mutex
               
    waitQSem b2
    signalQSem b2
    
    thread count mutex b1 b2 time (n + (1::Int))

main :: IO ()
main = do
   count <- newIORef 0
   mutex <- newQSem 1
   b1 <- newQSem 0
   b2 <- newQSem 1
   forM_ [1.. totalThread] (\time-> forkIO $ thread count mutex b1 b2 time (0::Int))
   threadDelay 1000