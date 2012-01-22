import Network
import Control.Monad
import Control.Concurrent
import System.IO

main :: IO()
main = listenOn (PortNumber 4242) >>= fork >> wait
  where
    wait = forever getChar
    fork socket =  replicateM 5 $ forkIO work
      where
        work = do
          tid <- (myThreadId >>= (\x -> return $ show x))
          putStrLn $ "child " ++ tid ++ " accepting on port 4242"
          forever $ do
            (h, _, _) <- accept socket
            message <- hGetLine h
            let msg = "child " ++ tid ++ " echo> " ++ message ++ ""
                write = hPutStr h
                getline = hGetLine h
                flush = hFlush h
                close =  hClose h
            write msg >> flush >> putStrLn msg >> close