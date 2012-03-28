module Main where

main :: IO ()
main = do
    从控制台获得一行字符 `然后` 在屏幕上输出
    在屏幕上输出 "Hello, world"

在屏幕上输出 :: String -> IO ()
在屏幕上输出 = putStrLn

从控制台获得一行字符 :: IO String
从控制台获得一行字符 = getLine

然后 :: Monad m => m a -> (a -> m b) -> m b
然后 = (>>=)
