module Tree where

data Tree a = Empty
            | Leaf a
            | Branch a (Tree a) (Tree a)
              deriving Eq

data Order = Pre
           | Mid
           | Post

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

instance Functor Tree where
    fmap = treeMap
        where
          treeMap _ Empty      = Empty
          treeMap f (Leaf a)   = Leaf (f a)
          treeMap f (Branch a l r) = Branch (f a) (treeMap f l) (treeMap f r)

-- | conver a Tree to List
toList :: Tree a -> Order -> [a]
toList Empty _ = []
toList (Leaf a) _ = [a]
toList (Branch a l r) ord =
    case ord of
      Pre  -> a : toList l ord ++ toList r ord
      Mid  -> toList l ord ++ [a] ++ toList r ord
      Post -> toList l ord ++ toList r ord ++ [a]


-- | insert a new element into a tree
insert :: Ord a => a -> Tree a -> Tree a
insert x Empty          = Leaf x
insert x (Leaf n)       = if x > n
                              then Branch n Empty (Leaf x)
                              else Branch n (Leaf x) Empty
insert x (Branch n l r) = if x > n
                              then Branch n l (insert x r)
                              else Branch n (insert x l) r

-- | find a subtree whose root is specificid element using deepth first search
findTreeDFS :: Eq a => a -> Tree a -> Tree a
findTreeDFS _ Empty             = Empty
findTreeDFS x (Leaf a)          = if a == x then Leaf a else Empty
findTreeDFS x t@(Branch a l r)
    | a == x = t
    | otherwise = if fl /= Empty
                      then fl
                      else findTreeDFS x r
                  where fl = findTreeDFS x l

-- | find specified element in a tree using deepth first search
findElemDFS :: Eq a => a -> Tree a -> Maybe a
findElemDFS x t = getElem $ findTreeDFS x t

-- | find specified element in a tree using binary search
findElemBST :: Ord a => a -> Tree a -> Maybe a
findElemBST _ Empty = Nothing
findElemBST k (Leaf x) = if k == x then Just x else Nothing
findElemBST k (Branch x l r)
    | k == x = Just x
    | k < x = findElemBST k l
    | otherwise = findElemBST k r

getElem :: Tree a -> Maybe a
getElem Empty          = Nothing
getElem (Leaf a)       = Just a
getElem (Branch a _ _) = Just a

deepth :: Tree a -> Int
deepth Empty          = 0
deepth (Leaf _)       = 1
deepth (Branch _ l r) = 1 + max (deepth l) (deepth r)

rotate :: Tree a -> Tree a
rotate x = x

reflect :: Tree a -> Tree a
reflect Empty = Empty
reflect (Leaf x) = Leaf x
reflect (Branch x l r) = Branch x (reflect r) (reflect l)

balanced :: Tree a -> Bool
balanced (Branch _ l r) = balanced l && balanced r && (deepth l == deepth r)
balanced _ = True

labalTree :: Num a => Tree t -> Tree (t, a)
labalTree tree = fst $ labalTreeIter tree 1
  where
    labalTreeIter t s =
        case t of
          Empty -> (Empty, s)
          Leaf x -> (Leaf (x, s), s + 1)
          Branch n l r -> (Branch (n, s) nl nr, sr)
            where
              (nl, sl) = labalTreeIter l (s + 1)
              (nr, sr) = labalTreeIter r sl

testTree2 :: Tree Char
testTree2 = Branch 'a'
            (Branch 'b' (Leaf 'c') (Leaf 'd'))
            (Branch 'e' (Leaf 'x') (Leaf 'f'))

testTree :: Tree Integer
testTree = Branch 8 (Branch 4 (Leaf 3) (Leaf 5)) (Branch 9 Empty (Leaf 10))
