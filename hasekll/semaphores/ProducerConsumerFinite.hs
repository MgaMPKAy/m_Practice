module Main where

import Control.Concurrent
import Data.IORef
import System.IO
import Control.Monad

producer :: IORef String -> QSemN -> QSemN -> QSemN -> IO b
producer buffer bmutex avalid space = do
    c <- getChar
    waitQSemN space 1
    waitQSemN bmutex 1
    myThreadId >>= (\i -> print $ show i ++ " produce " ++ [c])
    modifyIORef buffer (\x -> x ++ [c])
    signalQSemN bmutex 1
    signalQSemN avalid 1
    producer buffer bmutex avalid space


consumer :: IORef String -> QSemN -> QSemN -> QSemN -> IO b
consumer buffer bmutex avalid space = do
    waitQSemN avalid 1
    waitQSemN bmutex 1
    pd <- fmap head $ readIORef buffer
    modifyIORef buffer (drop 1)
    signalQSemN bmutex 1
    signalQSemN space 1
    consume pd
    consumer buffer bmutex avalid space
  where
    consume x = do
        myThreadId >>= (\i -> print $ show i ++ " god " ++ [x])
        threadDelay (10 ^ 6)

main :: IO ()
main = do
    hSetBuffering stdin NoBuffering
    buffer <- newIORef []
    avalid <- newQSemN 0
    bmutex <- newQSemN 1
    space  <- newQSemN 4
    replicateM_ 2 $ forkIO $ producer buffer bmutex avalid space
    replicateM_ 1 $ forkIO $ consumer buffer bmutex avalid space
    forever $ threadDelay (10 ^ 10)
