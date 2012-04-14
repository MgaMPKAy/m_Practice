{-# LANGUAGE TypeFamilies, MultiParamTypeClasses #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, OverloadedStrings #-}
{-# LANGUAGE FlexibleContexts, GADTs #-}

import Yesod
import Yesod.Form
import Text.Lucius (luciusFileReload)
import Text.Julius (juliusFileReload)
import Database.Persist
import Database.Persist.Sqlite
import Database.Persist.TH
import Data.Time
import Control.Applicative ((<$>), (<*>),(<|>), pure)
import Data.Text (Text)
import qualified Data.Text as T
import Data.Text.Encoding (encodeUtf8)
import Data.Maybe (isJust)
import Data.Aeson (FromJSON, decode, json')
import Data.Attoparsec (IResult(..), parse, maybeResult, endOfInput, feed)
import Data.ByteString (empty)
import Text.Pandoc
import Text.JSON.Generic

data JsonDB = JsonDB ConnectionPool

share [mkPersist sqlSettings, mkMigrate "migrateAll"] [persist|
JsonEntry
  text Text
  addTime UTCTime default=now
  author Text Maybe
  description Text Maybe
|]


mkYesod "JsonDB" [parseRoutes|
/ HomeR GET
/json JsonR GET POST
/json/#JsonEntryId ShowJsonR GET
|]
instance Yesod JsonDB

instance RenderMessage JsonDB FormMessage where
    renderMessage _ _ = defaultFormMessage

instance YesodPersist JsonDB where
  type YesodPersistBackend JsonDB = SqlPersist
  runDB action = do
        JsonDB pool <- getYesod
        runSqlPool action pool

main = withSqlitePool "test.db" 10 $ \pool-> do
    runSqlPool (runMigration migrateAll) pool
    warpDebug 8080 (JsonDB pool)

getJsonR :: Handler RepHtml
getJsonR =
    defaultLayout [whamlet| ^{recentEntries} |]

getHomeR :: Handler RepHtml
getHomeR = do
    (jsonFormWidget, enctype) <- generateFormPost jsonForm
    formId <- newIdent
    defaultLayout $ do
        $(whamletFile "home.hamlet")
        toWidget $(luciusFileReload "home.lucius")

postJsonR :: Handler RepHtml
postJsonR = do
    ((result, jsonFormWidget), enctype) <- runFormPost jsonForm
    case result of
      FormSuccess jsonEntry -> do
          populateAtuthorSession (jsonEntryAuthor jsonEntry)
          jid <- runDB $ insert $ jsonEntry
          redirect (ShowJsonR jid)

      _ -> do
          formId <- newIdent
          defaultLayout $ do
          $(whamletFile "home.hamlet")
          toWidget $(luciusFileReload "home.lucius")

  where
    populateAtuthorSession mauthor =
        case mauthor of
              Nothing -> deleteSession "author"
              Just val -> setSession "author" val

getShowJsonR :: JsonEntryId -> Handler RepHtml
getShowJsonR jid = do
    jsonEntry <- runDB $ get404 jid
    defaultLayout $ do
        $(whamletFile "showJson.hamlet")
        toWidget $(luciusFileReload "showJson.lucius")

jsonField :: (RenderMessage master FormMessage) => Field sub master Textarea
jsonField = checkBool validateJson ("Not valid json"::Text) textareaField
  where
    validateJson = isJust . maybeResult . flip feed empty
                   . (parse $ json' >> endOfInput) . encodeUtf8 . unTextarea

jsonForm :: Html -> MForm JsonDB JsonDB (FormResult JsonEntry, Widget)
jsonForm tokenHtml = do
    mauthor <- lift $ lookupSession "author"
    (jsonRes, jsonView) <- mreq jsonField "" Nothing
    (authorRes, authorView) <- mopt textField "" (Just mauthor)
    (descRes, descView) <- mopt textField "" Nothing

    formInputId <- lift $ newIdent
    submitId <- lift $ newIdent
    time <- liftIO getCurrentTime

    let jsonInputRes =
            JsonEntry . unTextarea <$> jsonRes
               <*> pure time
               <*> authorRes
               <*> descRes
        widget = do
            $(whamletFile "jsonForm.hamlet")
            toWidget $(luciusFileReload "jsonForm.lucius")
    return (jsonInputRes, widget)


recentEntries :: Widget
recentEntries = do
    mpage <- lift $ runInputGet $ id <$> iopt intField "page"
    let pageNumber = case mpage of
                       Just x -> x
                       Nothing -> 1
        entrisPerPage = 10
        dbQuery = selectList []
                  [ Desc JsonEntryAddTime
                  , LimitTo entrisPerPage
                  , OffsetBy $ (pageNumber - 1) * entrisPerPage
                  ]
    entries <- lift $ runDB $ dbQuery
    $(whamletFile "recentEntries.hamlet")
    toWidget $(luciusFileReload "recentEntries.lucius")
    toWidget $(juliusFileReload "recentEntries.julius")

{--
myWriterOptions = defaultWriterOptions {writerHtml5 = True}

jsonToHtml :: Text -> Html
jsonToHtml = writeHtml
    myWriterOptions . (\_ -> decodeJSON) defaultParserState . T.unpack
--}