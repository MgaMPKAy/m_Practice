> {-# LANGUAGE TypeFamilies, TemplateHaskell, QuasiQuotes #-}
> {-# LANGUAGE MultiParamTypeClasses #-}

> import Yesod

> data Fib = Fib

> mkYesod "Fib" [parseRoutes|
> /fib/#Int FibR GET
> /fib ConstantFibR GET
> |]
> instance Yesod Fib

> getFibR :: Int -> Handler RepHtml
> getFibR n = defaultLayout [whamlet|
> <p> fib #{n} = #{fib n}
> <a href=@{FibR (succ 1)}> Next
> <a href=@{FibR (pred 1)}> Next
> |]

> getConstantFibR :: Handler RepHtml
> getConstantFibR = defaultLayout [whamlet| #{fib 40} |]

> fib :: Int -> Int
> fib n
>     | n < 2 = 1
>     | otherwise = fib (n - 1) + fib (n - 2)

> main = warp 3000 Fib
