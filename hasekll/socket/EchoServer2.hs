module Main where

import Control.Concurrent
import Control.Exception
import Control.Monad
import Network
import System.IO
import Text.Printf


type Logger = String -> IO ()

main :: IO ()
main = do
    log <- logger

    sock <- listenOn (PortNumber 4000)
    forkIO (server log sock)

    log "Press enter to exit"
    fmap (const ()) getLine


    where
    logger :: IO Logger
    logger = do
        logVar <- newEmptyMVar
        forkIO . forever $ takeMVar logVar >>= putStrLn
        return (putMVar logVar)

    server :: Logger -> Socket -> IO ()
    server log sock =
        forever $ do
            (h, caddr, cport) <- accept sock
            log (printf "Connection from %s" caddr)
            hSetBuffering h NoBuffering

            forkIO $ (hGetContents h >>= hPutStr h)
                     `finally` hClose h