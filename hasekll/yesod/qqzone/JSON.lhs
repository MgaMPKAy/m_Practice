> {-# LANGUAGE TypeFamilies, TemplateHaskell, QuasiQuotes #-}
> {-# LANGUAGE MultiParamTypeClasses, OverloadedStrings #-}

> import Yesod
> import Result

> data JSON = JSON

> mkYesod "JSON" [parseRoutes|
> /json JsonR GET
> |]
> instance Yesod JSON

> getJsonR :: Handler RepJson
> getJsonR = jsonToRepJson $ Result "success" [XY 1 2, XY 2 3]

> main = warp 3000 JSON
