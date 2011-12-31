module Main where

import Control.Concurrent
import Control.Monad
import Data.IORef

main :: IO ()
main = do
    arrivedCount <- newIORef 0
    barrier <- newQSem 0
    arrivedMutex <- newQSem 1
    forM_ [1..totalThread] (\i -> forkIO $ thread i arrivedCount arrivedMutex barrier (0::Int))
    threadDelay (1000 * 1000)

thread :: Int -> IORef Int -> QSem -> QSem -> Int -> IO ()
thread i arrivedCount arrivedMutex barrier n = do
    myThreadId >>= (\i -> putStrLn $ show i ++ "\tRendezvous" ++ show n)
    threadDelay (i * 100000)
    waitQSem arrivedMutex
    modifyIORef arrivedCount (+1)
    c <- readIORef arrivedCount
    signalQSem arrivedMutex
    
    if (c == totalThread)
       then signalQSem barrier
       else waitQSem barrier         
    signalQSem barrier
    myThreadId >>= (\i -> putStrLn $ show i ++ "\tAfter" ++ show n)

totalThread :: Int
totalThread = 5