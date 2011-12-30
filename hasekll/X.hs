module Main where

import Graphics.X11.Xlib
import Control.Concurrent

main :: IO ()
main = do
    initThreads
    d <- openDisplay ""
    let s = defaultScreen d
    -- putStrLn $ resourceManagerString d
    -- putStrLn $ displayString d
    print $ displayWidthMM d s
    print $ displayHeightMM d s
    let screen = screenOfDisplay d s
    root <- rootWindow d s
    ---createSimpleWindow::  Display -> Window -> Position -> Position -> Dimension -> Dimension -> CInt -> Pixel -> Pixel -> IO Window
    window <- createSimpleWindow d root 0 0 100 100  100  (blackPixelOfScreen screen) (whitePixelOfScreen screen)
    mapWindow d window
    flush d
    getChar
    closeDisplay d
    return ()