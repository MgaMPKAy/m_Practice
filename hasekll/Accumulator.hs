module Accumulator where

import Data.IORef

makeAccumulator n = do
    acc <- newIORef n
    return $ func acc
  where
    func acc n = do
        before <-  readIORef acc
        writeIORef acc (before + n)
        return $ before + n
