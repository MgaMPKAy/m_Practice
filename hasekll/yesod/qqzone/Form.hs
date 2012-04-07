{-# LANGUAGE TemplateHaskell, QuasiQuotes, TypeFamilies #-}
{-# LANGUAGE OverloadedStrings, MultiParamTypeClasses #-}

import Yesod
import Control.Applicative ((<$>), (<*>))
import Data.Text (Text)
import Data.Text.Encoding (encodeUtf8)
import Data.Maybe (isJust)
import Data.Aeson (FromJSON, decode, json')
import Data.Attoparsec (parse, maybeResult, endOfInput, feed)
import Data.ByteString (empty)

data JsonForm = JsonForm

mkYesod "JsonForm" [parseRoutes|
/ JsonR GET POST
|]
instance Yesod JsonForm


instance RenderMessage JsonForm FormMessage where
    renderMessage _ _ = defaultFormMessage

getJsonR = defaultLayout [whamlet|
<form method=post action=@{JsonR}>
  <p>Json
  <input type=text name=json>
  <p><input type=submit>
|]

-- data JsonInput = JsonInput Text deriving (Show)

postJsonR :: Handler RepHtml
postJsonR = do
    Textarea jsonInput  <- runInputPost $ id <$> ireq jsonField "json"
    defaultLayout [whamlet| #{jsonInput} |]
  where
    form :: FormInput s JsonForm Textarea
    form = id <$> ireq textareaField "json"

    errorMessage :: Text
    errorMessage = "Not valid json"

    jsonField :: Field s JsonForm Textarea
    jsonField = checkBool validateJson errorMessage textareaField

    validateJson = isJust . maybeResult . flip feed empty
                   . (parse $ json' >> endOfInput) . encodeUtf8 . unTextarea


main = warpDebug 3000 JsonForm
