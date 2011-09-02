import Control.Concurrent
import Control.Monad
import GHC.Conc

main = do
  t <- forkIO p
  (\l -> putStrLn l) =<< (\s -> return (show s)) =<< (threadStatus t)
  (\l -> putStrLn l) =<< (\s -> return (show s)) =<< (threadStatus t)
  getChar
  (\l -> putStrLn l) =<< (\s -> return (show s)) =<< (threadStatus t)

p = do
  threadDelay 1000000
  putStrLn "A"
  threadDelay 1000000
  reportStackOverflow
