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
    line <- getLine
    sendAll sock line serverAddr
    now <- recvAll sock (length line)
    putStrLn now
    sClose sock

recvAll :: Socket -> Int -> IO String
recvAll sock n = do
    (str, numRecved, _) <- recvFrom sock 100
    if n == numRecved
       then return str
       else do
           sstr <- recvAll sock (n - numRecved)
           return $ str ++ sstr

sendAll :: Socket -> String -> SockAddr -> IO Int
sendAll _ [] _ = return 0
sendAll sock line addr = do
    numSended <- sendTo sock line addr
    if numSended == 0
       then return numSended
       else do
           numSended2 <- sendTo sock (drop numSended line) addr
           return $ numSended2 + numSended
