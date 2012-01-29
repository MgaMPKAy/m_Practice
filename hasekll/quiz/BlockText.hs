module Main where

import System.IO
import System.Environment

main :: IO ()
main = do
    (file:column:row:_) <- getArgs
    readFile file
       >>= return . (toBlock (read column) (read row))
       >>= mapM_ putStrLn

toBlock :: Int -> Int -> String -> [String]
toBlock column row string = toBlockH 0 column row longline
  where
    toBlockH n col row lline
        | length lline <= col = [lline]
        | n == row = "" : toBlockH 0 col row lline
        | otherwise = take col lline :
                      toBlockH (n + 1) col row (drop col lline)
    longline = filter (not . (`elem` illegelChars)) string
    illegelChars = ['\'', '\"', '\n', ' ', '\t']

