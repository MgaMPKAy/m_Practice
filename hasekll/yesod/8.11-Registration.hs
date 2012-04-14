{-# LANGUAGE TemplateHaskell, QuasiQuotes, OverloadedStrings #-}
{-# LANGUAGE TypeFamilies, MultiParamTypeClasses #-}

import Yesod
import qualified Data.Text as T

data Registration = Registration

mkYesod "Registration" [parseRoutes|
/ HomeR GET
/show ShowR POST
|]
instance Yesod Registration

getHomeR :: Handler RepHtml
getHomeR = do
    mname <- lookupSession "name"
    defaultLayout [whamlet|
<form action=@{ShowR} method=post>
  $maybe name <- mname
    Name <input type=text value=#{name} name=name>
  $nothing
    Name <input type=text name=name>
  <input type=submit>
|]

postShowR :: Handler RepHtml
postShowR = do
    mname <- lookupPostParam "name"
    case mname of
      Nothing -> redirect HomeR
      Just name ->
          if (T.null name)
              then do
                  deleteSession "name"
                  redirect HomeR
              else do
                  setSession "name" name
                  defaultLayout [whamlet| Name -> #{name} |]


main = warpDebug 8080 Registration
