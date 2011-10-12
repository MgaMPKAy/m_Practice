import Control.Concurrent
import Control.Exception
import Control.Monad


decreasePrint :: Num a => Int -> a -> Int -> IO ()
decreasePrint tid n delay= do
    let str = "#" ++ show tid ++ " " ++ show n
    threadDelay $ delay
    putStrLn str
    unless (n == 1) $ decreasePrint tid (n - 1) tid

main :: IO ()
main = do
    putStrLn "wait for all thread"
    mvars <- forM [1..5] $ \tid -> do
           mvar <- myFork $ decreasePrint tid 5 (tid * 100000)
           return mvar
    mapM_ takeMVar mvars
          
    
    putStrLn "run every thread in sequence"
    forM_ [1..5] $ \tid -> do
           mvar <- myFork $ decreasePrint tid 5 tid
           takeMVar mvar
           
    putStrLn "just fork 5 threads"
    forM_ [1..5] $ \tid -> do
           myFork $ decreasePrint tid 5 (tid * 100000)
                    
myFork :: IO () -> IO (MVar ())
myFork io = do
    mvar <- newEmptyMVar
    forkIO $ (io `finally` putMVar mvar ())
    return mvar