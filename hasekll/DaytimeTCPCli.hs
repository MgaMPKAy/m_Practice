module Main where

import Network.Socket
import System.Environment
import System.Exit
import Control.Monad

main :: IO ()
main = do
    args <- getArgs
    when (length args < 1) $ 
         print "usage: DaytimeTCPCli <IPaddress>" >> exitFailure

    let port = (PortNum 8080)              
    serverAddr <- return . SockAddrInet port
               =<< inet_addr (head args) 

    sock <- socket AF_INET Stream defaultProtocol
    connect sock serverAddr
    (str, _, _) <- recvFrom sock 100
    putStrLn str
    sClose sock
