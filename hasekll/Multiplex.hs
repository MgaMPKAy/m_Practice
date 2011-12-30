module Main where

import Control.Concurrent
import Control.Monad
import Data.IORef

thread :: IORef Int -> QSem -> IO ()
thread  count mutex = do
    waitQSem mutex
    modifyIORef count (+ 1)
    doSometing count
    signalQSem mutex
    where doSometing count =
              myThreadId >>= putStr . show 
              >> putStr "\t" 
              >> readIORef count >>= print
              >> threadDelay 1000000

main :: IO ()
main = do
    mutex <- newQSem 3
    count <- newIORef 0
    forM_ [1..5] (\_ -> forkIO $ forever $ thread count mutex)
    forM_ [1..5] (\_ -> forkIO $ forever $ thread count mutex)
    threadDelay $ 1000000 * 20
