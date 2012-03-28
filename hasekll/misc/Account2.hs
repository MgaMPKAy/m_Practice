module Account2 where

import Data.IORef

data Account = Account {unBalance :: IORef Int}
data Command = Desposit | Withdraw  deriving (Show, Read, Eq)


makeAccount :: Int -> IO (Command -> Int -> IO Int)
makeAccount balance = do
    acc <- fmap Account (newIORef balance)
    return $ dispatch acc
  where
    dispatch acc command =
        case command of
          Withdraw -> withdraw acc
          Desposit -> desposit acc

    withdraw acc amount = do
        currentBalance <- readIORef (unBalance acc)
        let newBalance = currentBalance - amount
        if (newBalance >= 0)
            then writeIORef (unBalance acc) newBalance
                 >> return newBalance
            else error "Insuccficent balance"

    desposit acc amount = do
        currentBalance <- readIORef (unBalance acc)
        let newBalance = currentBalance + amount
        writeIORef (unBalance acc) newBalance
        return newBalance
