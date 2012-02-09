module Main where

import Control.Concurrent
import Control.Monad
import Data.IORef

totalFollower :: Int
totalFollower = 10

leader :: QSemN  -> QSemN -> IORef Int -> IORef Int -> QSemN -> QSemN -> IO ()
leader leaderQueue followerQueue leaders followers mutex rendezvous = do
    waitQSemN mutex 1
    f <- readIORef followers
    if f > 0
        then do
            modifyIORef followers (\x -> x - 1)
            signalQSemN followerQueue 1
        else do
            modifyIORef leaders (+1)
            signalQSemN mutex 1
            waitQSemN leaderQueue 1
    dance "Leader"
    waitQSemN rendezvous 1
    signalQSemN mutex 1

follower ::  QSemN -> QSemN -> IORef Int -> IORef Int -> QSemN -> QSemN -> IO ()
follower leaderQueue followerQueue leaders followers mutex rendezvous = do
    waitQSemN mutex 1
    l <- readIORef leaders
    if l > 0
        then do
            modifyIORef leaders (\x -> x - 1)
            signalQSemN leaderQueue 1
        else do
            modifyIORef followers (+1)
            signalQSemN mutex 1
            waitQSemN followerQueue 1

    dance "Follower"
    signalQSemN rendezvous 1

dance name = do
    myThreadId >>= (\i -> putStrLn $ show i ++ "\t" ++ name ++ " Dancing")
    threadDelay (10^6)

main :: IO ()
main = do
    lsem <- newQSemN 0
    fsem <- newQSemN 0
    mutex <- newQSemN 1
    rendezvous <- newQSemN 0
    ls <- newIORef 0
    fs <- newIORef 0
    replicateM_ totalFollower $ forkIO $ follower lsem fsem ls fs mutex rendezvous
    replicateM_ totalFollower $ forkIO $ leader lsem fsem ls fs mutex rendezvous

    getChar >>  return ()
