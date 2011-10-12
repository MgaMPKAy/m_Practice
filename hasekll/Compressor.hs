
import Control.Concurrent (forkIO)
import Control.OldException (handle)
import qualified Data.ByteString.Lazy as L
import System.Console.Readline (readline)
import Codec.Compression.GZip


main :: IO ()
main = do
    maybeLine <- readline "File name"
    case maybeLine of
      Nothing -> return ()
      Just "" -> return ()
      Just name -> do
           handle  print $ do
                       content <- L.readFile name
                       forkIO (compressFile name content)
                       return ()
           main
  where compressFile path = L.writeFile (path ++ ".gz") .compress