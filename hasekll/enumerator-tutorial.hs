{-# LANGUAGE OverloadedStrings #-}
module EnumDir where

import Control.Monad.IO.Class (MonadIO, liftIO)
import Data.ByteString (ByteString)
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BC
import Data.Enumerator hiding (map, filter)
import qualified Data.Enumerator.Binary as EB
import qualified Data.Enumerator.List as EL
import Data.Maybe
import System.IO

consumer :: Iteratee BS.ByteString IO ()
consumer = do
    mw <- EB.head
    case mw of
      Nothing -> return ()
      Just w  -> do
          liftIO . putStr $ "XXX"
          liftIO . BC.putStrLn . BS.singleton $ w
          consumer

listFeeder :: Enumerator ByteString IO a
listFeeder = enumList 1 ["12", "34"]

fileFeeder :: Enumerator ByteString IO a
fileFeeder = EB.enumFile "EnumDir.hs"

consumer2 :: Iteratee BS.ByteString IO ()
consumer2 = do
    mw <- EB.head
    case mw of
      Nothing -> return ()
      Just w  -> do
          liftIO . putStr $ "YYY"
          liftIO . BC.putStrLn . BS.singleton $ w

enumHandleLine :: MonadIO m => Integer -> Handle -> Enumerator ByteString m ByteString
enumHandleLine n hdl =
    EB.enumHandle n hdl $= byteLines


byteLines :: Monad m => Enumeratee ByteString ByteString m b
byteLines = EB.splitWhen (== 10)


