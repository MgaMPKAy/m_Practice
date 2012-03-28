module Main where

import System.IO
import System.Environment
import Control.Concurrent

main = do
    (filename:_) <-getArgs
    handle <- openFile filename ReadMode
    hSeek handle SeekFromEnd 0
    loop handle
  where
    loop h = do
        eof <- hIsEOF h
        if eof
           then threadDelay 10000
           else hGetLine h >>= putStrLn
        loop h
        