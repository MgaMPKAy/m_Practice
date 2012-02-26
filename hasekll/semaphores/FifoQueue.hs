{-# LANGUAGE ParallelListComp #-}

module Main where

import Control.Concurrent
import Control.Applicative
import Control.Monad
import Data.IORef
import Data.List

data Fifo = Fifo {
      unMutex :: QSem
    , unQueue :: IORef [QSem]
}

waitFifo :: Fifo -> IO ()
waitFifo fifo = do
    h <- newQSem 0
    waitQSem (unMutex fifo)
    modifyIORef (unQueue fifo) (\l -> l ++ [h])
    signalQSem (unMutex fifo)
    waitQSem h

signalFifo :: Fifo -> IO ()
signalFifo fifo = do
    waitQSem (unMutex fifo)
    (h:t) <- readIORef (unQueue fifo)
    signalQSem h
    writeIORef (unQueue fifo) t
    signalQSem (unMutex fifo)

newFifo :: IO Fifo
newFifo =  Fifo <$> newQSem 1 <*> newIORef []

thread :: Fifo -> IO ()
thread fifoq = do
    myThreadId >>= waitFifoWithName fifoq . show
    myThreadId >>= (\tid -> putStrLn $ show tid ++ "\tok")

total :: Int
total = 6

main :: IO ()
main = do
    fifo <- newFifo
    let act =  concat [[a,b] | a <- (replicate total $ thread fifo)
                             | b <- (replicate total $ yield >> thread fifo)]
    -- let actx = intercalate [(yield >> thread fifo)] (replicate total $ [thread fifo])
    mapM_ forkIO act
    replicateM_ (total * 2) $ getChar >> signalFifo fifo
    getChar >> return ()


waitFifoWithName :: Fifo -> String -> IO ()
waitFifoWithName fifo name = do
    h <- newQSem 0
    waitQSem (unMutex fifo)
    putStrLn $ name ++ " waiting"
    modifyIORef (unQueue fifo) (\l -> l ++ [h])
    signalQSem (unMutex fifo)
    waitQSem h
