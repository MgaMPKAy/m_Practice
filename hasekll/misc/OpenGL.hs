
import Graphics.Rendering.OpenGL
import Graphics.UI.GLUT

main :: IO ()
main = do
     (progname, _) <- getArgsAndInitialize
     createWindow "Hello, World"
     displayCallback $= display2
     mainLoop

myPoints :: [(GLfloat,GLfloat,GLfloat)]
myPoints = map (\k -> (sin (2*pi*k/12), cos(2*pi*k/12), 0.0)) [1..12]

display :: IO ()
display = do
    clear [ColorBuffer]
    renderPrimitive Triangles $ mapM_ (\(x,y,z) -> vertex $ Vertex3 x y z) myPoints
    flush

display2 = do 
  clear [ColorBuffer]
  renderPrimitive Quads $ do
    color $ (Color3 (1.0::GLfloat) 0 0)
    vertex $ (Vertex3 (0::GLfloat) 0 0)
    vertex $ (Vertex3 (0::GLfloat) 0.2 0)
    vertex $ (Vertex3 (0.2::GLfloat) 0.2 0)
    vertex $ (Vertex3 (0.2::GLfloat) 0 0)
    color $ (Color3 (0::GLfloat) 1 0)
    vertex $ (Vertex3 (0::GLfloat) 0 0)
    vertex $ (Vertex3 (0::GLfloat) (-0.2) 0)
    vertex $ (Vertex3 (0.2::GLfloat) (-0.2) 0)
    vertex $ (Vertex3 (0.2::GLfloat) 0 0)
    color $ (Color3 (0::GLfloat) 0 1)
    vertex $ (Vertex3 (0::GLfloat) 0 0)
    vertex $ (Vertex3 (0::GLfloat) (-0.2) 0)
    vertex $ (Vertex3 ((-0.2)::GLfloat) (-0.2) 0)
    vertex $ (Vertex3 ((-0.2)::GLfloat) 0 0)
    color $ (Color3 (1::GLfloat) 0 1)
    vertex $ (Vertex3 (0::GLfloat) 0 0)
    vertex $ (Vertex3 (0::GLfloat) 0.2 0)
    vertex $ (Vertex3 ((-0.2::GLfloat)) 0.2 0)
    vertex $ (Vertex3 ((-0.2::GLfloat)) 0 0)
  flush