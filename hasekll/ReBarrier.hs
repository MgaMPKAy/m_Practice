module Main where

import Control.Concurrent
import Control.Monad
import Data.IORef

totalThread :: Int
totalThread = 3

thread :: Show a => IORef Int -> QSem -> QSem -> QSem -> Int -> a -> IO b
thread count mutex b1 b2 i n = do
    threadDelay (i * 100000)
    myThreadId >>= (\tid -> putStrLn $ show tid ++ "\t" ++ show n)
        
    waitQSem mutex
    modifyIORef count (+1)
    c1 <- readIORef count
    when (c1 == totalThread) $ do
            writeIORef count 0
            waitQSem b2
            signalQSem b1
    signalQSem mutex

    waitQSem b1
    signalQSem b1

    waitQSem mutex
    modifyIORef count (subtract 1)
    c2 <- readIORef count
    when (c2 == totalThread) $ do
            writeIORef count 0
            waitQSem b1
    signalQSem mutex
               
    waitQSem b2
    signalQSem b2
    
    thread count mutex b1 b2 (i + 1) n

main :: IO ()
main = do
   count <- newIORef 0
   mutex <- newQSem 1
   b1 <- newQSem 0
   b2 <- newQSem 1
   forM_ [1.. totalThread] (\i-> forkIO $ thread count mutex b1 b2 i (0::Int))
   threadDelay (1000 * 10000)