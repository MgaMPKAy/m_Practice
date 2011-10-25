module Main where

import Network.Socket
import Control.Monad
import System.IO
import Data.Time

main = withSocketsDo $ do
    let port = PortNum 8080
    serverAddr <- return . SockAddrInet port
               =<< inet_addr "127.0.0.1"

    sock <- socket AF_INET Stream defaultProtocol
    bindSocket sock serverAddr
    listen sock 10
    acceptLoop sock
    sClose sock

  where
    acceptLoop sock = do
           (client, addr) <- accept sock
           putStrLn $ show addr ++  " connectted"
           now <- return . show =<< getCurrentTime
           sendTo client now addr
           sClose client
           acceptLoop sock