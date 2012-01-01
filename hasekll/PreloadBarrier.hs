module Main where

import Control.Concurrent
import Control.Monad
import Data.IORef

totalThread :: Int
totalThread = 5

thread count mutex b1 b2 time n = do
    myThreadId >>= (\tid -> putStrLn $ show tid ++ "\t" ++ show n ++ "\tRend")
        
    waitQSem mutex
    modifyIORef count (+1)
    c1 <- readIORef count
    when (c1 == totalThread) $ do
            signalQSemN b1 totalThread
    signalQSem mutex

    waitQSemN b1 1

    myThreadId >>= (\tid -> putStrLn $ show tid ++ "\t" ++ show n ++ "\tCritic")

    waitQSem mutex
    modifyIORef count (subtract 1)
    c2 <- readIORef count
    when (c2 == 0) $ do
            signalQSemN b2 totalThread
    signalQSem mutex
               
    waitQSemN b2 1
    
    thread count mutex b1 b2 time (n + (1::Int))

main :: IO ()
main = do
   count <- newIORef 0
   mutex <- newQSem 1
   b1 <- newQSemN 0
   b2 <- newQSemN 1
   forM_ [1.. totalThread] (\time-> forkIO $ thread count mutex b1 b2 time (0::Int))
   threadDelay 1000000