module echo_client

import TCPIP
import StdEnv
import StdLib

Start world
  # (mip, world) = lookupIPAddress "127.0.0.1" world
  | isNothing mip = abort "lookupIPAddress"
  | otherwise
  # (succ, mchan, world) = connectTCP_MT (Just 10) (fromJust mip, 3000) world
  | succ <> TR_Success = abort "connectTCP_MT"
  | otherwise
  # chan  = fromJust mchan
    rchan = chan.rChannel
    schan = chan.sChannel
    (console, world) = stdio world
  = echoClient rchan schan console world

echoClient rchan schan console world
  # (input, console) = freadline console
  | input == ":quit\n"
    # (succ, world) = fclose console world
      world = closeChannel schan world
    = closeRChannel rchan world
  | otherwise
    # (schan, world) = send (toByteSeq input) schan world
      (result, rchan, world) = receive rchan world
      console = fwrites (toString result) console
    = echoClient rchan schan console world
