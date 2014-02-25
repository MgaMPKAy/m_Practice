module echo_server

import TCPIP
import StdEnv
import StdLib

import StdDebug

:: *Server = { rchans  :: *(TCP_Pair *TCP_RChannels *TCP_Listeners)
             , schans  :: *TCP_SChannels
             , timeout :: Maybe Int
             }

newServer port world
  #! (succ, mlistener, world) = openTCP_Listener port world
  | not succ = abort "openTCP_Listener\n"
  | otherwise
  #! listener = fromJust mlistener
  = ({ rchans  = TCP_Pair (TCP_RChannels []) (TCP_Listeners [listener])
     , schans  = TCP_SChannels []
     , timeout = Just 900
    }, world)

serverLoop (server, world)
  #! (events, rchans, _ , world) = selectChannel_MT server.timeout
                                                    server.rchans
                                                    TCP_Void
                                                    world
     server = {server & rchans = rchans}
  | isEmpty events = serverLoop (server, world)
  | otherwise      = eventLoop events (server, world)

eventLoop [] (server, world)                         = serverLoop (server, world)
eventLoop [(idx, SR_Available):t] (server, world)    = eventLoop t (handleAvalable idx server world)
eventLoop [(idx, SR_EOM) : t] (server, world)        = eventLoop t (removeClient idx server world)
eventLoop [(idx, SR_Disconnected):t] (server, world) = eventLoop t (removeClient idx server world)
eventLoop [(idx, _):t] (server, world)               = eventLoop t (server, world)

removeClient idx server world
  #! (TCP_Pair (TCP_RChannels rchans) listener) = server.rchans
     (r, rchans) = removeAt` idx rchans
     world = closeRChannel r world
     rchans = (TCP_Pair (TCP_RChannels rchans) listener)
     new_server = {server & rchans = rchans}

     (TCP_SChannels schans) = new_server.schans
     (s, schans) = removeAt` idx schans
     world = closeChannel s world
     schans = (TCP_SChannels schans)
     new_server = {new_server & schans = schans}
  = (new_server, world)
  where
    removeAt` idx ls = (\ (i, t) -> (hd i, t)) (loop (zip2 [0..] ls) [] [])
      where
        loop [] item acc = (item, acc)
        loop [(i,s):t] item acc
          | i <> idx  = loop t item [s:acc]
          | otherwise = loop t [s:item] acc

handleAvalable idx server world
  #! (nr, rchans) = getNrOfChannels server.rchans
     (TCP_Pair (TCP_RChannels rchans) (TCP_Listeners [listener:_])) = rchans
     (TCP_SChannels schans) = server.schans
  | idx + 1 == nr
      // Accept connection
      #! ((addr,chans), listener, world) = receive listener world
          // It's safe to append new channel to the end
         rchans = (TCP_Pair (TCP_RChannels (rchans ++ [chans.rChannel])) (TCP_Listeners [listener]))
         server = {server & rchans = rchans, schans = TCP_SChannels (schans ++ [chans.sChannel])}
      =  (server, world)
  | otherwise
      // Receive message and send it back
      #! (result, rchans, world) = recvIdx idx rchans world
         (schans, world) = sendIdx idx result schans world

         rchans = (TCP_Pair (TCP_RChannels rchans) (TCP_Listeners [listener]))
         server = {server & rchans = rchans, schans = (TCP_SChannels schans)}
      =  (server, world)

recvIdx idx rchans world :== loop (zip2 [0..] rchans) world
  where
    loop [] world = (toByteSeq "", [], world)
    loop [(i,r):t] world
      | i <> idx
          #! (msg, t, world) = loop t world
          =  (msg,[r:t], world)
      | otherwise
          #! (msg, r, world) = receive r world
             (_, t, world) = loop t world
          = (msg, [r:t], world)

sendIdx idx msg schans world :== loop (zip2 [0..] schans) world
  where
    loop [] world = ([], world)
    loop [(i,s):t] world
      | i <> idx
          #! (t, world) = loop t world
          =  ([s:t], world)
      | otherwise
          #! (s, world) = send msg s world
             (t, world) = loop t world
          = ([s:t], world)

Start world
  #! (server, world) = newServer 3000 world
  = serverLoop (server, world)
