{-# LANGUAGE TemplateHaskell, QuasiQuotes, OverloadedStrings #-}
{-# LANGUAGE MultiParamTypeClasses, TypeFamilies #-}

import Yesod
import Control.Applicative ((<$>), (<*>))
import Data.Text (Text)

data ThreeParams = ThreeParams

mkYesod "ThreeParams" [parseRoutes|
/ ThreeParamR GET
|]
instance Yesod ThreeParams

instance RenderMessage ThreeParams FormMessage where
    renderMessage _ _ = defaultFormMessage

form :: Html -> MForm ThreeParams ThreeParams (FormResult (Text, Text, Text), Widget)
form = renderDivs $ (,,)
       <$> areq textField "param1" Nothing
       <*> areq textField "param2" Nothing
       <*> areq textField "param3" Nothing

getThreeParamR :: Handler RepHtml
getThreeParamR = do
    ((result, widget), enctype) <- runFormGet form
    case result of
            FormSuccess (p1, p2, p3) -> do
                defaultLayout [whamlet|
<p> Param1 : #{p1}
<p> Param2 : #{p2}
<p> Param3 : #{p3}
|]
            _ -> do
                defaultLayout [whamlet|
<form method=get action=@{ThreeParamR} enctype=#{enctype}>
  ^{widget}
  <input type=submit value=Submit>
|]

main = warp 8080 ThreeParams