import Control.Concurrent
import Control.Exception
import Control.Monad

decreasePrint :: Int -> Int -> IO()
decreasePrint tid n = do
    let str = "#" ++ show tid ++ " " ++ show n
    putStrLn str
    threadDelay 100
    unless (n == 1) decreasePrint tid (n - 1)

main :: IO ()
main = do
    forM_ [1..5] $ \tid -> do
           mvar <- myFork $ decreasePrint tid 5
           takeMVar mvar
                    
myFork :: IO () -> IO (MVar ())
myFork io = do
    mvar <- newEmptyMVar
    forkIO $ (io `finally` putMVar mvar ())
    return mvar