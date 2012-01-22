import Control.Concurrent
import Control.Monad

decreasePrint :: Int -> Int -> IO()
decreasePrint tid n = do
    let str = "#" ++ show tid ++ " " ++ show n
    putStrLn str
    threadDelay 1000000
    if n == 1
        then return ()
        else decreasePrint tid (n - 1)

main :: IO Char
main = do
    forM_ [1..5] $ \tid -> forkIO $ decreasePrint tid 5
    getChar