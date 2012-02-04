module PointInPloygon where

-- module PointInPloygon
--     (
--      Point(..)
--     , Polygon(..)
--     , Relation(..)
--     , pointInPolygon
--     , relation
--     ) where

data Point = Point {
      unX :: Float
    , unY :: Float
    } deriving (Show, Eq)

data Polygon = Polygon [Point] deriving (Show, Eq)

data Relation = Inside | Outside | On deriving (Show)

data Line =Line Point Point deriving (Show,Eq)

data Rect = Rect {
      left :: Float
    , right :: Float
    , top :: Float
    , bottom :: Float
} deriving (Show, Eq)

polyToRect :: Polygon -> Rect
polyToRect (Polygon points) =
    Rect{left = minimum xs
        ,right = maximum xs
        ,top = maximum ys
        ,bottom = minimum ys
} where xs = [x | Point x _ <- points]
        ys = [y | Point _ y <- points]

pointInRect :: Point -> Rect -> Bool
pointInRect p r =
    unX p >= left r &&
    unX p <= right r &&
    unY p >= bottom r &&
    unY p <= top r


polygonToLines :: Polygon -> [Line]
polygonToLines (Polygon points) = pointsToLines points

pointsToLines :: [Point] -> [Line]
pointsToLines points_ = buildLines $ points_ ++ [head points_]
  where
    buildLines [] = []
    buildLines [_] = []
    buildLines [p1,p2] = [Line p1 p2]
    buildLines (p1:p2:ps) = Line p1 p2 : buildLines (p2:ps)

intersectant ::Point -> Line -> Int
intersectant (Point x y) (Line (Point x1 y1) (Point x2 y2))
    | y < minY || y > maxY || x < minX = 0
    | minY == maxY  = if x >= minX && x <= maxX then -1 else 0
    | x0 > x        = 0
    | x0 == x       = -1
    | y == minY     = 0
    | otherwise     = 1
  where
    minX = min x1 x2
    minY = min y1 y2
    maxX = max x1 x2
    maxY = max y1 y2
    x0 = x1 + (y - y1) * (x2 -x1) / (y2 - y1)

pointInPolygon :: Point -> Polygon -> Bool
pointInPolygon point polygon =
    case point `relation` polygon of
      Inside -> True
      _ -> False

relation :: Point -> Polygon -> Relation
relation point polygon
    | not $ point `pointInRect` polyToRect polygon = Outside
    | any (==(-1)) flags = On
    | odd count = Inside
    | otherwise = Outside
  where count = sum [f | f <- flags, f > 0]
        flags = map (point `intersectant`) (polygonToLines polygon)


test_poly :: Polygon
test_poly = Polygon [Point 1 0, Point 2 1, Point 1 2, Point 0 1]

test_point :: Point
test_point = (Point 1 1)

test_rect :: Rect
test_rect = Rect 0 2 2 0

test1 :: Bool
test1 = pointInPolygon test_point test_poly

test2 :: Bool
test2 = pointInRect test_point test_rect

test3 :: Bool
test3 = pointInRect test_point (polyToRect test_poly)

test :: [Bool]
test = map (`pointInPolygon` test_poly) [Point 1 1, Point 1 0, Point 0 0]
