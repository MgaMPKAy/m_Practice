{-# LANGUAGE DeriveDataTypeable #-}

import Control.Concurrent
import Control.Monad
import System.IO

producer mvar n = do
    threadDelay 50000
    putMVar mvar n
    putStrLn $ "Produced " ++ show n
    producer mvar (n + 1)

consummer mvar = do
    product <- takeMVar mvar
    tid <- myThreadId
    putStrLn $ "Consummed " ++ show product ++ " by " ++ show tid
    consummer mvar

main :: IO Char
main = do
    hSetBuffering stdout NoBuffering
    mvar <- newEmptyMVar
    forkIO $ consummer mvar
    forkIO $ consummer mvar
    forkIO $ consummer mvar
    forkIO $ producer mvar 0
    forkIO $ producer mvar 100
    getChar
