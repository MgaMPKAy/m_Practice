module Cont where

import Control.Monad.Cont
import System.IO

calculateLength :: [a] -> Cont r Int
calculateLength l = return (length l)


double :: Int -> Cont r Int
double n = return (n * 2)

whatsYourName :: String -> String
whatsYourName name = 
    (`runCont` id) $
        callCC $ \exit -> do
            validateName name exit
            return $ "Welcome, " ++ name ++ "!"
        
validateName name exit =
    when (null name) (exit "You forget to tell me your name!")
               
main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    runContT (callCC askString) reportResult
    
askString :: (String -> ContT () IO String) -> ContT () IO String
askString next = do
    liftIO $ putStrLn "Please enter a string"
    s <- liftIO getLine
    next s
        
reportResult :: String -> IO () 
reportResult s = putStrLn ("You entered: " ++ s)

foo :: Int -> Cont r String
foo n =
    callCC $ \k -> do
        let n' = n ^ 2 + 3
        when (n' > 20) $ k "over twenty"
        return (show $ n' - 4)

bar :: Char -> String -> Cont r Int
bar c s = do
    msg <- callCC $ \k -> do
        let s' = c : s
        when (s' == "hello") $ k "They say hello."
        let s'' = show s'
        return ("They appear to be saying " ++ s'')
    return (length msg)


inc :: Int -> Int -> Cont b Int
inc n x = do
    callCC $ \_ -> return $ x + n

dev :: Int -> Int -> Cont b Int
dev n x = do
    callCC $ \_ -> return $ x - n

