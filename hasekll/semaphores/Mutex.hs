module Main where

import Control.Concurrent
import Control.Applicative
import Control.Monad (forever)
import Data.IORef

data Mutex = Mutex {
      unMutex :: QSem
}

newMutex :: IO Mutex
newMutex = pure Mutex <*> newQSem 1

lock :: Mutex -> IO ()
lock (Mutex m) = waitQSem m

unlock :: Mutex -> IO ()
unlock (Mutex m) = signalQSem m

thread :: String -> IORef Int -> Mutex -> IO ()
thread name count mutex = do
    lock mutex
    modifyIORef count (+ 1)
    putStr $ "Thread" ++ name ++ ":\t"
    readIORef count >>= print
    unlock mutex

main :: IO ()
main = do
    mutex <- newMutex
    count <- newIORef 0
    forkIO $ forever $ thread "A" count mutex
    forkIO $ forever $ thread "B" count mutex
    threadDelay 1000
