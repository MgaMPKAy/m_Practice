module SimpleGraphics where

import Graphics.SOE.Gtk

main0 = runGraphics $ do
    w <- openWindow "Window" (300, 300)
    drawInWindow w $ withColor Red (text (100, 200) "Hello World")
    drawInWindow w pic1
    drawInWindow w pic2
    sierpinkTri w 100 100 256
    spaceClose w 

spaceClose :: Window -> IO()
spaceClose w = do
    k <- getKey w
    if k == ' ' 
        then closeWindow w
        else spaceClose w

pic1 = withColor Red $ ellipse (150, 150) (300, 200)
pic2 = withColor Blue $ polyline [(100, 50), (200,50)
                                 ,(200, 250), (100,250), (100, 50)]

fillTri w x y size = 
    drawInWindow w $ withColor Blue $
                 polygon [(x,y), (x+size,y), (x,y - size), (x,y)]

minSize = 8

sierpinkTri w x y size =
    if size <= minSize
       then fillTri w x y size
       else let size2 = size `div` 2
            in do sierpinkTri w x y size2
                  sierpinkTri w x (y - size2) size2
                  sierpinkTri w (x + size2) y size2
                  