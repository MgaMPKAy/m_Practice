{-# LANGUAGE TemplateHaskell, QuasiQuotes, TypeFamilies #-}
{-# LANGUAGE OverloadedStrings, MultiParamTypeClasses #-}

import Yesod
import Text.Lucius
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

data ValidJson = ValidJson {unJson :: Text} deriving (Show)

jsonForm :: Html -> MForm JsonForm JsonForm (FormResult ValidJson, Widget)
jsonForm =
    renderDivs $ (ValidJson . unTextarea) <$> areq jsonField "json" Nothing
  where
    errorMessage :: Text
    errorMessage = "Not valid json"

    jsonField :: Field s JsonForm Textarea
    jsonField = checkBool validateJson errorMessage textareaField

    validateJson = isJust . maybeResult . flip feed empty
                   . (parse $ json' >> endOfInput) . encodeUtf8 . unTextarea

getJsonR = do
    ((_, widget), enctype)<- generateFormPost jsonForm
    defaultLayout $ do
        formId <- lift newIdent
        toWidget $(luciusFileReload "jsonForm.lucius")
        toWidget $(whamletFile "jsonForm.hamlet")

postJsonR :: Handler RepHtml
postJsonR = do
    ((result, widget), enctype)  <- runFormPost jsonForm
    case result of
      FormSuccess jsonInput ->
          defaultLayout $ do
               formId <- lift newIdent
               $(whamletFile "showJson.hamlet")
               toWidget $(luciusFileReload "showJson.lucius")
      _ -> defaultLayout $ do
               formId <- lift newIdent
               toWidget $(whamletFile "jsonForm.hamlet")
               toWidget $(luciusFileReload "jsonForm.lucius")

main = warpDebug 3000 JsonForm
