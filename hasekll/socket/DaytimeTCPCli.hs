module Main where

import Network.Socket
import System.Environment
import System.Exit
import System.IO
import Control.Monad

main :: IO ()
main = withSocketsDo $ do
    args <- getArgs
    when (length args < 1) $
         print "usage: DaytimeTCPCli <IPaddress>" >> exitFailure

    addrinfo <- getAddrInfo Nothing (Just (head args)) (Just "1300")
    let serverAddr = addrAddress (head addrinfo)

    sock <- socket AF_INET Stream defaultProtocol
    connect sock serverAddr
    handle <- socketToHandle sock ReadMode
    putStrLn =<< hGetLine handle
    hClose handle
