module Main where

import Control.Concurrent
import Control.Monad
import Data.IORef

main = do
    arrivedCount <- newIORef 0
    barrier <- newQSem 0
    arrivedMutex <- newQSem 1

    forM_ [1.. totalThread] (\_ -> forkIO $ thread arrivedCount arrivedMutex barrier)
    threadDelay 1000000

thread :: IORef Int -> QSem -> QSem -> IO ()
thread arrivedCount arrivedMutex barrier = do
    myThreadId >>= (\i -> putStrLn $ show i ++ "\tRendezvous")
    
    waitQSem arrivedMutex
    modifyIORef arrivedCount (+1)
    c <- readIORef arrivedCount
    signalQSem arrivedMutex
    
    if (c == totalThread)
       then signalQSem barrier
       else waitQSem barrier         
    signalQSem barrier    

    
    myThreadId >>= (\i -> putStrLn $ show i ++ "\tAfter barrier...")

totalThread :: Int
totalThread = 5