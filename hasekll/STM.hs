module STM where

import Data.IORef
import Control.Concurrent
import Control.Concurrent.STM

type  IAccount = IORef Integer

transferI :: Integer -> IAccount -> IAccount -> IO()
transferI amount from to = do
    fromVal <- readIORef from
    toVal <- readIORef to
    writeIORef from (fromVal - amount)
    writeIORef to (toVal + amount)

type MAccount = MVar Integer
creditM :: Integer -> MAccount -> IO()
creditM amount account = do
    current <- takeMVar account
    putMVar account (current + amount)

debitM :: Integer -> MAccount -> IO()
debitM amount account = do
    current <- takeMVar account
    putMVar account (current - amount)

transferM :: Integer -> MAccount -> MAccount ->IO()
transferM amount from to = do
    debitM amount from
    creditM amount to

type AccountS = TVar Integer

creditS :: Integer -> AccountS -> STM()
creditS amount account = do
    current <- readTVar account
    writeTVar account (current + amount)
debitS :: Integer -> AccountS -> STM()
debitS amount account = do
    current <- readTVar account
    writeTVar account (current - amount)
transferS :: Integer -> AccountS -> AccountS -> STM()
transferS amount from to = do
    debitS amount from
    creditS amount to

repeatIO :: Integer -> IO a -> IO a
repeatIO 1 m = m
repeatIO n m = m >> repeatIO (n - 1) m