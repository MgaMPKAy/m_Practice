module Main where

import Network.Socket
import System.Environment
import System.Exit
import Control.Monad

main = do
    args <- getArgs
    when (length args < 2) $
         putStrLn "Please specific an IP address" 
         >> putStrLn "Usage: SumClient ip num"
	 >> exitFailure
         
    addrinfo <- getAddrInfo Nothing (Just (head args)) (Just "1300")
    let serverAddr = addrAddress (head addrinfo)

    sock <- socket AF_INET Stream defaultProtocol
    connect sock serverAddr
    sendTo sock (args !! 1) serverAddr
    (str, _, _) <- recvFrom sock 100
    putStrLn str
    sClose sock
