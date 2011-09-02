data Tree1 = Tree1Leaf
           | Tree1Node (Integer, Char) Tree1 Tree1 Tree1
           deriving Show

data Tree2 = Tree2Leaf
           | Tree2Node Integer [Tree2]
           deriving Show

data BinTree a = BinLeaf
               | BinNode a (BinTree a) (BinTree a)
               deriving Show

inorder :: BinTree a -> [a]
inorder BinLeaf = []
inorder (BinNode x t1 t2) = inorder t1 ++ [x] ++ inorder t2

preorder :: BinTree a -> [a]
preorder BinLeaf = []
preorder (BinNode x t1 t2) = [x] ++ preorder t1 ++ preorder t2

postorder :: BinTree a -> [a]
postorder BinLeaf = []
postorder (BinNode x t1 t2) = postorder t1 ++ postorder t2 ++ [x]

inorderf :: (a->b) -> BinTree a -> [b]
inorderf _ BinLeaf = []
inorderf f (BinNode x t1 t2) = inorderf f t1 ++ [(f x)] ++ inorderf f t2

reflect :: BinTree a -> BinTree a
reflect BinLeaf = BinLeaf
reflect (BinNode x t1 t2) = BinNode x (reflect t2) (reflect t1)

height :: BinTree a -> Integer
height BinLeaf = 0
height (BinNode x t1 t2) = 1 + max (height t1) (height t2)

size :: BinTree a -> Int
size BinLeaf = 0
size (BinNode x t1 t2) = 1 + size t1 + size t2

balanced :: BinTree a -> Bool
balanced BinLeaf = True
balanced (BinNode x t1 t2) =
  balanced t1 && balanced t2 && (height t1 == height t2)

bstSearch :: Ord a => a -> BinTree (a, b) -> Maybe b
bstSearch key BinLeaf = Nothing
bstSearch key (BinNode (x, y) t1 t2) =
  if key == x
     then Just y
  else if key < x
          then bstSearch key t1
       else bstSearch key t2

insert :: Ord a => (a, b) -> BinTree (a, b) -> BinTree (a, b)
insert (key, d) BinLeaf = BinNode (key, d) BinLeaf BinLeaf
insert (key, d) (BinNode (x, y) t1 t2) =
  if key == x
     then BinNode (key, d) t1 t2
  else if key < x
          then BinNode (x, y) (insert (key, d) t1) t2
       else BinNode (x, y) t1 (insert (key, d) t2)

mapTree :: (a -> b) -> BinTree a -> BinTree b
mapTree _ BinLeaf = BinLeaf
-- mapTree f (BinNode x t1 t2) =


flatten_aux :: BinTree a -> [a] -> [a]
flatten_aux BinLeaf ks = ks
flatten_aux (BinNode  x t1 t2) ks = flatten_aux t1 (x : flatten_aux t2 ks)
flatten :: BinTree a -> [a]
flatten t = flatten_aux t []

-- test
bintree1 = (BinNode 1
            (BinNode 2
             (BinNode 3
              BinLeaf BinLeaf)
             BinLeaf)
            (BinNode 4
             (BinNode 5
              BinLeaf BinLeaf)
             BinLeaf))
