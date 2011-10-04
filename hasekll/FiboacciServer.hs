{-# LANGUAGE TypeFamilies, QuasiQuotes, MultiParamTypeClasses,
             TemplateHaskell, OverloadedStrings #-}
import Yesod
import Network.Wai.Handler.Warp

data Fibonacci  = Fibonacci

mkYesod "Fibonacci" [parseRoutes|
/  FibonacciR GET
|]

instance Yesod Fibonacci where
    approot _ = ""

getFibonacciR :: Handler RepHtml
getFibonacciR = defaultLayout [whamlet| #{show $ fibonacci 40} |]

main :: IO ()
main = toWaiApp Fibonacci >>= runSettings (defaultSettings {settingsHost = "0.0.0.0"})

fibonacci :: Int -> Int
fibonacci n
    | n < 2 = 1
    | otherwise = fibonacci (n - 1) + fibonacci(n - 2)