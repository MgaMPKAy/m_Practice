import System.INotify
import System.Environment

{- usage: FileMonitor [filenames] -}

main = do
    files <- getArgs
    mapM_ watch files
    getChar
        where 
          watch f = do
              inotify <- initINotify
              addWatch inotify [AllEvents] f $ \e -> print e

