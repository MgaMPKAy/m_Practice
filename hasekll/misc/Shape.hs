module Shape where

data Shape = Rectangle Side Side
           | Ellipse Radius Radius
           | RtTriangle Side Side
           | Polygon [Vertex]
             deriving (Show)

type Radius = Float
type Side   = Float
type Vertex = (Float, Float)

rectangle :: Side -> Side -> Shape
rectangle x y  = Polygon [(0, 0), (0, y),
                          (x, 0), (x, y)]

rtTriangle :: Side -> Side -> Shape
rtTriangle x y  = Polygon [(0, 0), (x, 0), (0, y)]


regularPolygon :: Int -> Side -> Shape
regularPolygon n side = Polygon $ map (\a -> (sin a * r, cos a * r)) angles
    where r = abs $ side * sin ((pi - angle) / 2) / sin angle 
          angles = take n $ iterate (+angle) 0
          angle = 2 * pi  / fromIntegral n

area :: Shape -> Float
area (Ellipse r1 r2)    = pi * r1 * r2
area (Rectangle s1 s2)  = s1 * s2
area (RtTriangle s1 s2) = s1 * s2 / 2
area (Polygon (v1:vs))  = polyArea vs
    where polyArea (v2:v3:vs') = triArea v1 v2 v3
                                 + polyArea (v3:vs')
          polyArea _           = 0

triArea :: Vertex -> Vertex -> Vertex -> Float
triArea v1 v2 v3 = let a = distBetween v1 v2
                       b = distBetween v2 v3
                       c = distBetween v3 v1
                       s = 0.5 * (a + b + c)
                   in sqrt (s * (s - a) * (s - b) * (s - c))

distBetween :: Vertex -> Vertex -> Float
distBetween (x1, y1) (x2, y2) = 
    sqrt ((x1 - x2)^2 + (y1 - y2)^2)

convex :: Shape -> Bool
convex (Rectangle _ _)  = True
convex (Ellipse _ _)    = True
convex (RtTriangle _ _) = True
convex (Polygon []) = True