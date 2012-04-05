> {-# LANGUAGE TypeFamilies, TemplateHaskell, QuasiQuotes #-}
> {-# LANGUAGE MultiParamTypeClasses, OverloadedStrings #-}

> import Yesod

> data HelloWorld = HelloWorld

> mkYesod "HelloWorld" [parseRoutes|
> / RootR GET
> |]
> instance Yesod HelloWorld

> getRootR :: Handler RepHtml
> getRootR = defaultLayout $ do
>     setTitle $ "Hello"
>     [whamlet| <h>Hello, world! |]

> main = warp 3000 HelloWorld