module Main where

import Network.Socket
import Control.Monad
import System.IO
import Control.Exception
import Prelude hiding(catch)

main = withSocketsDo $ do
    addrinfo <- getAddrInfo
                (Just (defaultHints {addrFlags = [AI_PASSIVE]}))
                Nothing
                (Just "1300")
    let serverAddr = addrAddress (head addrinfo)
    sock <- socket AF_INET Stream defaultProtocol
    bindSocket sock serverAddr
    listen sock 10
    acceptLoop sock 0
    sClose sock

  where
    acceptLoop sock acc = do
           (client, addr) <- accept sock
           putStrLn $ show addr ++  " connectted"
           (strNum, _ , _)  <- catch (recvFrom client 100) 
                               (clientClosedHandler sock acc addr)
           let num = read strNum
           sendTo client (show (num + acc))addr
           sClose client
           acceptLoop sock (num + acc)

    clientClosedHandler sock acc addr e = do
        print (e::IOException)                         
        return ("", 0, addr)
        acceptLoop sock acc
