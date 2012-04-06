> {-# LANGUAGE TemplateHaskell, QuasiQuotes, MultiParamTypeClasses #-}
> {-# LANGUAGE TypeFamilies, OverloadedStrings #-}

> import Yesod
> import Text.Julius (juliusFileReload)
> import Text.Lucius (luciusFileReload)
> import Text.Hamlet (hamletFile)

> data Template = Template

> mkYesod "Template" [parseRoutes|
> / HomeR GET
> |]
> instance Yesod Template

> getHomeR :: Handler RepHtml
> getHomeR = defaultLayout $ do
>     buttonA
>     buttonA

> buttonA = do
>     buID <- lift newIdent
>     addScriptRemote "https://ajax.googleapis.com/ajax/libs/jquery/1.7.2/jquery.min.js"
>     toWidget $(hamletFile "button.hamlet")
>     toWidget $(luciusFileReload "button.lucius")
>     toWidgetBody $(juliusFileReload "button.julius")


> main = warpDebug 3000 Template
