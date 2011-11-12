module LogicGate where

import Data.IORef
import Control.Monad

data Wire   = Wire {
      unSignal  :: IORef Signal,
      unActions :: IORef [Action],
      unLable   :: String
    }
data Signal = Low | Hig | X deriving (Eq, Show)

type Action = IO ()
type WireAction = Wire -> Action

makeWire :: String -> IO Wire
makeWire label = do
    defaultSignal <- newIORef X
    defaultActions <- newIORef []
    return $ Wire defaultSignal defaultActions label

setSignal :: Wire -> Signal -> IO ()
setSignal wire newSignal = do
    oldSignal <- readIORef (unSignal wire)
    actions <- readIORef (unActions wire)
    when (oldSignal /= newSignal) $
         writeIORef (unSignal wire) newSignal >>
         sequence_ actions

addAction :: Wire -> WireAction -> IO ()
addAction wire wireaction = do
    actions <-readIORef (unActions wire)
    let newAction = wireaction wire
    writeIORef (unActions wire) (newAction : actions)

getSignal :: Wire -> IO Signal
getSignal wire = readIORef (unSignal wire)


data Agenda = Agenda

orGate :: Wire -> Wire -> Wire -> IO ()
orGate wi1 wi2 wo = do
    s1 <- getSignal wi1
    s2 <- getSignal wi2
    let o = if (s1 == Hig || s2 == Hig) then Hig else Low
    setSignal wo o

andGate :: Wire -> Wire -> Wire -> IO ()
andGate wi1 wi2 wo = do
    s1 <- getSignal wi1
    s2 <- getSignal wi2
    let o = if (s1 == Hig && s2 == Hig) then Hig else Low
    setSignal wo o

printSingal :: WireAction
printSingal wire = do
    putStr $ unLable wire 
    putStr "->"
    getSignal wire >>= print


test :: IO ()
test = do
    w1 <- makeWire "a"
    w2 <- makeWire "b"
    addAction w1 printSingal
    setSignal w1 Hig
    setSignal w2 Low
    andGate w1 w2 w1
