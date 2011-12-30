module Main where

import Control.Concurrent
import Control.Monad (forever)
import Data.IORef

thread :: String -> IORef Int -> QSem -> IO ()
thread name count mutex = do
    waitQSem mutex
    modifyIORef count (+ 1)
    putStr $ "Thread" ++ name ++ ":\t"
    readIORef count >>= print
    signalQSem mutex

main :: IO ()
main = do
    mutex <- newQSem 1
    count <- newIORef 0
    forkIO $ forever $ thread "A" count mutex
    forkIO $ forever $ thread "B" count mutex
    threadDelay 1000