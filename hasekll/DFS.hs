{-# LANGUAGE ExistentialQuantification #-}
module DFS where

import Data.Array

-- data Vertex  = forall a . Ix a => Vertex a
type Vertex   = Char
type Table a  = Array Vertex a
type Graph    = Table [Vertex]
type Edge     = (Vertex, Vertex)
type Bounds   = (Vertex, Vertex)

vertices :: Graph -> [Vertex]
vertices = indices

edges :: Graph -> [Edge]
edges g = [(v, w) | v <- vertices g, w <- g ! v]

mapT :: (Vertex -> a -> b) -> Table a -> Table b
mapT f t = array (bounds t) [(v, f v (t ! v)) | v <- indices t]

outdegree :: Graph -> Table Int
outdegree g = mapT numedges g
  where numedges v ws = length ws

buildG :: Bounds -> [Edge] -> Graph
buildG bnds es = accumArray (flip (:)) [] bnds es

testGraph :: Graph
testGraph = buildG ('a', 'j') [
              ('a', 'j'), ('a', 'g'), ('b', 'i')
            , ('b', 'a'), ('c', 'h'), ('c', 'e')
            , ('e', 'j'), ('e', 'h'), ('e', 'd')
            , ('f', 'i'), ('g', 'f'), ('g', 'b')
            ]

transposeG :: Graph -> Graph
transposeG g = buildG (bounds g) (reverseE g)

reverseE :: Graph -> [Edge]
reverseE g = [(w, v) | (v, w) <- edges g]

indegree :: Graph -> Table Int
indegree g = outdegree (transposeG g)

data Tree a = Node a (Forest a)
type Forest a = [Tree a]

dfs :: Graph -> [Vertex] -> Forest Vertex
dfs = undefined

dff :: Graph -> Forest Vertex
dff g = dfs g (vertices g)

preorder :: Tree a -> [a]
preorder (Node a ts) = [a] ++ preorderF ts

preorderF :: Forest a -> [a]
preorderF ts = concat (map preorder ts)

preOrd :: Graph -> [Vertex]
preOrd g = preorderF (dff g)

tabulate :: Bounds -> [Vertex] -> Table Int
tabulate bnds vs = array bnds (zip vs [1..])

preArr :: Bounds -> Forest Vertex -> Table Int
preArr bnds ts = tabulate bnds (preorderF ts)

postorder :: Tree a -> [a]
postorderF :: Forest a -> [a]
postorder (Node a ts) = postorderF ts ++ [a]

postorderF ts = concat (map postorder ts)

postOrd :: Graph -> [Vertex]
postOrd g = postorderF (dff g)

topSort :: Graph -> [Vertex]
topSort g = reverse (postOrd g)

components :: Graph -> Forest Vertex
components g = dff (undirected g)

undirected :: Graph -> Graph
undirected g = buildG (bounds g) (edges g ++ reverseE g)

scc :: Graph -> Forest Vertex
scc g = dfs (transposeG g) (reverse (postOrd g))

scc' :: Graph -> Forest Vertex
scc' g = dfs g (reverse (postOrd (transposeG g)))

generate :: Graph -> Vertex -> Tree Vertex
generate g v = Node v (map (generate g) (g ! v))

type Set s = MutArr s Vertex Bool

mkEmpty :: Bounds -> ST s (Set s)
mkEmpty bnds = newArr bnds False

contains m v = readArr m v