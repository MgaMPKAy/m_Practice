import Control.Concurrent
import Control.Monad
import System.Exit

incMVar :: MVar Int -> IO ()
incMVar mvar = do
    threadDelay 10000
    num <- takeMVar mvar
    putMVar mvar (num + 1)

printMVar1 :: MVar Int -> IO ()
printMVar1 mvar = do
    threadDelay 5000
    num <- takeMVar mvar
    putMVar mvar num
    when (num `mod` 2 /= 0) $ print "Error" >> exitSuccess

printMVar2 :: MVar Int -> IO ()
printMVar2 mvar = do
    threadDelay 10000
    num <- takeMVar mvar
    putMVar mvar num
    when (num `mod` 2 == 0) $ print num


main :: IO Char
main = do
    mvar <- newMVar 2
    forkIO (forever $ incMVar mvar)
    forkIO (forever $ incMVar mvar) 
    forkIO (forever $ printMVar1 mvar)
    forkIO (forever $ printMVar2 mvar)
    getChar