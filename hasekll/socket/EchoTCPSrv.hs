module Main where

import Network.Socket
import Control.Monad
import System.IO
import Control.Concurrent
import Control.Exception
import Prelude hiding(catch)

main :: IO ()
main = do
    addrinfo <- getAddrInfo
                (Just (defaultHints {addrFlags = [AI_PASSIVE]}))
                Nothing
                (Just "1300")
    let serverAddr = addrAddress (head addrinfo)
    print serverAddr
    sock <- socket AF_INET Stream defaultProtocol
    bindSocket sock serverAddr
    getSocketName sock >>= print
    listen sock 10
    acceptLoop sock
    sClose sock

  where
    acceptLoop sock = do
           (client, addr) <- accept sock
           forkIO $ (handleClinet client addr)
                      `catch` (handleExcption client)
           acceptLoop sock

    handleClinet client addr = do
           (str, _ , _) <- recvFrom client 128
           putStrLn $ "recv " ++ show (length str) ++ "\tbytes from\t" ++ show addr
           sendAll client str addr
           if str == "BYE\n"
               then closeClient client
               else handleClinet client addr

    handleExcption :: Socket -> IOException  -> IO ()
    handleExcption client _ = closeClient client

    closeClient client = sClose client >>
                         (putStrLn $ show client ++ " closed") >>
                         myThreadId >>= killThread


sendAll :: Socket -> String -> SockAddr -> IO Int
sendAll _ [] _ = return 0
sendAll sock line addr = do
    numSended <- sendTo sock line addr
    putStrLn $ "sent " ++ show numSended ++ "\tbytes to\t" ++ show addr
    if numSended == 0
       then return numSended
       else do
           numSended2 <- sendTo sock (drop numSended line) addr
           return $ numSended2 + numSended
