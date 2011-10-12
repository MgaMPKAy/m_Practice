{-# LANGUAGE TypeFamilies, QuasiQuotes, MultiParamTypeClasses,
             TemplateHaskell, OverloadedStrings #-}
import Yesod
import Network.Wai.Handler.Warp

data Fibonacci  = Fibonacci

mkYesod "Fibonacci" [parseRoutes|
/#Int  FibonacciR GET
|]

instance Yesod Fibonacci where
    approot _ = ""

-- getFibonacciR :: Handler RepHtml
getFibonacciR n = defaultLayout [whamlet| #{show $ fibonacci n} |]

main :: IO ()
main = toWaiApp Fibonacci >>= runSettings (defaultSettings {settingsHost = "0.0.0.0"})

fibonacci n
    | n < 2 = 1
    | otherwise = fibonacci (n - 1) + fibonacci(n - 2)