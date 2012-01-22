module Main where

import Network.Socket
import Control.Monad
import System.IO
import Data.Time

main :: IO ()
main = withSocketsDo $ do
    addrinfo <- getAddrInfo
                (Just defaultHints {addrFlags = [AI_PASSIVE]})
                Nothing
                (Just "1300")
    let serverAddr = addrAddress (head addrinfo)

    sock <- socket AF_INET Stream defaultProtocol
    bindSocket sock serverAddr
    listen sock 10
    acceptLoop sock
    sClose sock

  where
    acceptLoop sock = do
        (client, _) <- accept sock
        handle <- socketToHandle client WriteMode
        hSetBuffering handle LineBuffering
        hPutStrLn handle =<< return . show =<< getCurrentTime
        hClose handle
        acceptLoop sock
