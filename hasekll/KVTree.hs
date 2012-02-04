module KVTree where

data Tree k v
    = Empty
    | Node k v (Tree k v) (Tree k v)
      deriving (Eq)

data Order = Pre
           | Mid
           | Post
{--
instance Show a => Show (Tree a) where
    show t = showTree t 0
        where
          showTree t0 level =
              case t0 of
                Empty -> indent ++ "Empty"
                Leaf l -> indent ++ "Leaf: " ++ show l
                Branch n left right ->
                           indent ++ "Branch:" ++ show n ++ "\n" ++
                           showTree left (level + 1) ++ "\n" ++
                           showTree right (level + 1)
              where indent = replicate (level * 2) ' '
--}

instance Functor (Tree k) where
    fmap = treeMap
        where
          treeMap _ Empty          = Empty
          treeMap f (Node k v l r) =
              Node k (f v) (treeMap f l) (treeMap f r)

-- | conver a Tree to List
toList :: Tree k v -> Order -> [v]
toList Empty _ = []
toList (Node _ v l r) ord =
    case ord of
      Pre  -> v : toList l ord ++ toList r ord
      Mid  -> toList l ord ++ [v] ++ toList r ord
      Post -> toList l ord ++ toList r ord ++ [v]


-- | insert a new (k,v) pair  into a tree
insert :: Ord a => (a, v) -> Tree a v -> Tree a v
insert (k,v) Empty = Node k v Empty Empty
insert p@(k,_) n@(Node nk nv l r)
    | k < nk = Node nk nv (insert p l) r
    | k > nk = Node nk nv l (insert p r)
    | otherwise = n

-- | find a subtree whose root is specificid key using deepth first search
findTreeDFS :: (Eq k, Eq v) => k -> Tree k v -> Tree k v
findTreeDFS _ Empty             = Empty
findTreeDFS k t@(Node nk _  l r)
    | k == nk = t
    | otherwise = if fl /= Empty
                      then fl
                      else findTreeDFS k r
                          where fl = findTreeDFS k l

-- | find specified element in a tree using deepth first search
findElemDFS :: (Eq k, Eq v) => k -> Tree k v -> Maybe v
findElemDFS x t = getElem $ findTreeDFS x t

-- | find specified element in a tree using binary search
findElemBST :: Ord k => k-> Tree k v -> Maybe v
findElemBST _ Empty = Nothing
findElemBST k (Node nk v l r)
    | k == nk = Just v
    | k < nk = findElemBST k l
    | otherwise = findElemBST k r

getElem :: Tree k v -> Maybe v
getElem Empty          = Nothing
getElem (Node _ v _ _) = Just v

deepth :: Tree k v -> Int
deepth Empty          = 0
deepth (Node _ _ l r) = 1 + max (deepth l) (deepth r)

rotate :: t -> t
rotate x = x

reflect :: Tree k v -> Tree k v
reflect Empty = Empty
reflect (Node k v l r) = Node k v (reflect r) (reflect l)

balanced :: Tree k v -> Bool
balanced (Node _ _ l r) = balanced l && balanced r && (deepth l == deepth r)
balanced _ = True

testTree :: Tree Integer Integer
testTree = Node 1 8 (Node 2 4 (Node 3 1 Empty Empty) Empty) Empty
