module Account where

import Data.IORef

data Account = Account {balance :: IORef Int}
data Command = Desposit | Withdraw  deriving (Show, Read, Eq)

newAccount :: Int -> IO Account
newAccount initialBalance =
    newIORef initialBalance >>= return . Account

withdraw :: Int -> Account -> IO Int
withdraw amount account = do
    current <- readIORef $ balance account
    let remind = current - amount
    if remind >= 0
        then writeIORef (balance account) remind
             >> return remind
        else error "Insufficent funds"

desposit :: Int -> Account -> IO Int
desposit amount acconut = do
    current <- readIORef $ balance acconut
    writeIORef (balance acconut) (current + amount)
    return $ current + amount

makeAccount :: Int -> IO (Command -> Int -> IO Int)
makeAccount initialBalance = do
    account <- newAccount initialBalance
    return $ dispatch account
  where 
    dispatch :: Account -> Command -> Int -> IO Int
    dispatch account command amount = 
        case command of
          Withdraw -> withdraw amount account
          Desposit -> desposit amount account

makeSecureAccount :: Int -> String -> IO (Command -> Int -> String -> IO Int)
makeSecureAccount initialBalance password = do
    account <- newAccount initialBalance
    return $ dispatch account
  where
    dispatch account command amount guesspw = do
        if guesspw /= password
           then error "Error passwd"
           else case command of 
                  Withdraw -> withdraw amount account
                  Desposit -> desposit amount account
                                                   
           