module new_world

import TCPIP
import StdEnv
import StdLib

:: NewWorld :== Int

// We have one world and build another. Parallel universes!
new_world :: *World -> (*NewWorld, *World)
new_world w = (0, w)

// After our new world being destroyed, we move back to the original world.
destory_world :: *NewWorld *World -> *World
destory_world nw w = w

instance ChannelEnv NewWorld where
    // Same as World
    channelEnvKind env = (0, env)

    // Same as World
    mb_close_inet_receiver_without_id _ _ nw = nw

    // Time is stopped! (This will affect timeout calculation.)
    channel_env_get_current_tick env = (0, env)

Start world
    #! (nw, world) = new_world world
       (mip, nw) = lookupIPAddress "127.0.0.1" nw
    |  isNothing mip = abort "lookupIPAddress"
    |  otherwise
    #! (succ, mchan, nw) = connectTCP_MT (Just 10) (fromJust mip, 3000) nw
    |  succ <> TR_Success = abort "connectTCP_MT"
    |  otherwise
    #  chan  = fromJust mchan
       rchan = chan.rChannel
       schan = chan.sChannel
       (console, world) = stdio world
    =  echoClient rchan schan console (nw, world)

// We are working with two world, parallel universes
// But we have only one world at the end.

echoClient rchan schan console (world2, world)
  # (input, console) = freadline console
  | input == ":quit\n"
    # (succ, world) = fclose console world
      world2 = closeChannel schan world2
      world2 = closeRChannel rchan world2
    = destory_world world2 world
  | otherwise
    # (schan, world2) = send (toByteSeq input) schan world2
      (result, rchan, world2) = receive rchan world2
      console = fwrites (toString result) console
    = echoClient rchan schan console (world2, world)
