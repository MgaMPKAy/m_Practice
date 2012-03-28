module IOStack where

import Data.IORef
import Control.Monad

data IOStack a = IOStack {unIOStacj :: IORef [a]}

makeStack :: IO (IOStack a)
makeStack = liftM IOStack $ newIORef []

isEmptyIO :: IOStack a -> IO Bool
isEmptyIO (IOStack s) = liftM null (readIORef s)

peekIO :: IOStack a -> IO a
peekIO (IOStack s) = liftM head (readIORef s)

popIO :: IOStack a -> IO a
popIO (IOStack s) = do
    sl <- readIORef s
    writeIORef s (tail sl)
    return $ head sl

pushIO :: a -> IOStack a -> IO ()
pushIO e (IOStack s) = modifyIORef s (\ss -> e:ss)

sizeIO :: IOStack a -> IO Int
sizeIO (IOStack s) = liftM length $ readIORef s
