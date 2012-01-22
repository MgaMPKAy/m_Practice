module Main where

import qualified Data.Map as M
import System.Process
import System.Environment
import System.Exit

data Protocol = HTTPS | HTTP deriving Eq
instance Show Protocol where
    show HTTPS = "https://"
    show HTTP = "http://"

data Privacy = Incognito | Public deriving Eq
instance Show Privacy where
    show Incognito = " --incognito"
    show Public = " "

data App = App {
        unName :: String
      , unAppURL :: String
      , unProtocol :: Protocol
      , unPrivacy :: Privacy
    }
instance Show App where
    show app = baseCmd ++ "--app="
               ++ show (unProtocol app)
               ++ show (unAppURL app)
               ++ show (unPrivacy app)
               ++ " &"

apps:: [App]
apps = [ App "xiami" "www.xiami.com/song/play?ids=/song/playlist-default" HTTP Public
       , App "freenode" "webchat.freenode.net" HTTP Incognito
       , App "douban.fm" "douban.fm" HTTP Public
       , App "greader" "www.google.com/reader/view/?tab=Xy" HTTPS Public
       , App "gmail" "mail.google.com/mail/mu/mp/130/?mui=ca#tl/Inbox"  HTTPS Public
       , App "webqq" "webqq.qq.com" HTTP Incognito
       , App "douban" "douban.com" HTTP Public
       ]

baseCmd :: String
baseCmd = "nohup /usr/lib/chromium/chromium --user-data-dir=/tmp/chromium "

appsMap :: M.Map String App
appsMap = M.fromList $ map appToKV apps
  where
    appToKV :: App -> (String, App)
    appToKV app = (unName app, app)

appToCmd :: App -> String
appToCmd = show

main :: IO ()
main = do
    args <- getArgs
    case length args of
      1 -> runApp1 (head args)
      _ -> exitFailure
    return ()

runApp1 :: String -> IO ()
runApp1 appName = do
    let maybeApp = M.lookup appName appsMap
    _ <- case maybeApp of
           Nothing -> exitFailure
           Just app -> runCommand $ appToCmd app
    return ()
    