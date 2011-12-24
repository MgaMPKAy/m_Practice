import XMonad
import XMonad.Hooks.DynamicLog
import XMonad.Hooks.ManageDocks
import XMonad.Util.Run(spawnPipe)
import XMonad.Util.EZConfig(additionalKeysP)
import System.IO

myManageHook :: ManageHook
myManageHook = composeAll
    [ className =? "Gvbam"     --> doFloat
    , className =? "FloatWindow"      --> doFloat
    ]

myKeys :: [(String, X ())]
myKeys = [ ("M-w",                    kill)
         , ("M1-0",                   spawn "urxvtc")
         , ("M1--",                   spawn "a-ex")
         , ("M1-=",                   spawn "chromium --user-data-dir=/tmp/chromium --incognito")
         , ("M1-C-=",                 spawn "chromium --user-data-dir=/tmp/chromium")
         , ("M1-<F9>",                spawn "a-touchpad")
         , ("<Print>",                spawn "a-screenshot")
         , ("<XF86Tools>",            spawn "a-touchpad")
         , ("<XF86AudioMute>",        spawn "a-mixer-mute")
         , ("<XF86AudioLowerVolume>", spawn "a-mixer-down")
         , ("<XF86AudioRaiseVolume>", spawn "a-mixer-up")
         --, ("M-p",                 spawn "dmenu_run | dmenu -b")
         ]

myXmobar :: Handle -> PP
myXmobar proc = xmobarPP {
                  ppOutput = hPutStrLn proc
                , ppTitle = xmobarColor "green" "" . shorten 50
                }

myStartupHook :: X ()
myStartupHook = spawn "a-touchpad"

main :: IO ()
main = do
    xmproc <- spawnPipe "xmobar"
    xmonad $ defaultConfig
        { manageHook = manageDocks <+> myManageHook
                       <+> manageHook defaultConfig
        , layoutHook = avoidStruts  $  layoutHook defaultConfig
        , logHook = dynamicLogWithPP $ myXmobar xmproc
        , modMask = mod4Mask
        , normalBorderColor = "#dddddd"
        , focusedBorderColor = "#cdad00"
        , focusFollowsMouse = False
        , terminal = "urxvt"
        , startupHook = myStartupHook
        } `additionalKeysP` myKeys

{-
snippet
myKeymap = \c -> mkKeymap c $
           [ ("C-<Print>", spawn "sleep 0.2; gnome-screenshot -i")
           , ("<Print>", spawn "gnome-screenshot")
           , ("M1-0", spawn "gnome-terminal  --working-directory=/tmp/workspace --sm-client-disable")
           , ("M1--", spawn "a-ex")
           , ("M1-=", spawn "google-chrome")
           ]

`additionalKeys`
        [ ((controlMask, xK_Print), spawn "sleep 0.2; gnome-screenshot -i")
        , ((0, xK_Print), spawn "sleep 0.2; gnome-screenshot")
        , ((mod1Mask, xK_0), spawn "gnome-terminal  --working-directory=/tmp/workspace --sm-client-disable")
        , ((mod1Mask, xK_minus), spawn "a-ex")
        , ((mod1Mask, xK_equal), spawn "google-chrome")
        ]
-}