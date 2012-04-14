{-# LANGUAGE TemplateHaskell, QuasiQuotes, OverloadedStrings #-}
{-# LANGUAGE MultiParamTypeClasses, TypeFamilies #-}

import Yesod
import Control.Applicative ((<$>), (<*>))
import Data.Text (Text)

data AllParams = AllParams

mkYesod "AllParams" [parseRoutes|
/ AllParamsR GET
|]
instance Yesod AllParams

instance RenderMessage AllParams FormMessage where
    renderMessage _ _ = defaultFormMessage

getAllParamsR = do
    req <- getRequest
    defaultLayout [whamlet| #{show req} |]

main = warp 8080 AllParams

instance Show Request where
    show req = "GetParams: " ++ concatMap show (reqGetParams req) ++ "\n"
               ++ "Cookies: " ++ concatMap show (reqCookies req) ++ "\n"
--               ++ "WaiRequest: " ++  show (reqWaiRequest req) ++ "\n"
               ++ "Lang: " ++ concatMap show (reqLangs req) ++ "\n"
               ++ "Token: " ++ show (reqToken req) ++ "\n"
