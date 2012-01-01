module Main where

import Control.Concurrent
import Control.Monad

totalFollower :: Int
totalFollower = 10

leader :: QSemN -> QSemN -> IO ()
leader leaderQueue followerQueue = do
    myThreadId >>= (\i -> putStrLn $ show i ++ "\tLeader: Waiting for follower")
    signalQSemN leaderQueue 1
    waitQSemN followerQueue 1
    myThreadId >>= (\i -> putStrLn $ show i ++ "\tOK, i found follower")

follower :: QSemN -> QSemN -> IO ()
follower leaderQueue followerQueue = do
    signalQSemN followerQueue 1
    myThreadId >>= (\i -> putStrLn $ show i ++ "\tFollower: Waiting for follower")
    waitQSemN leaderQueue 1
    myThreadId >>= (\i -> putStrLn $ show i ++ "\tFollower: I find a leader")

main :: IO ()
main = do
    lsem <- newQSemN 0
    fsem <- newQSemN 0
    replicateM_ totalFollower $forkIO $ leader lsem fsem
    getChar
    replicateM_ totalFollower $ forkIO $ follower lsem fsem
    getChar >>  return ()
