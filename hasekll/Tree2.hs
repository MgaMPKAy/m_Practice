module Tree where

data Tree a = Empty
            | Leaf a
            | Branch a (Tree a) (Tree a)
              deriving (Show, Eq)


data Order = Pre
           | Mid
           | Post

-- | map a function to a tree and return a new tree
treeMap :: (a -> b) -> Tree a-> Tree b
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


insert :: Ord a => a -> Tree a -> Tree a
insert x Empty          = Leaf x
insert x (Leaf n)       = if x > n
                              then Branch n Empty (Leaf x)
                              else Branch n (Leaf x) Empty 
insert x (Branch n l r) = if x > n 
                              then Branch n l (insert x r)
                              else Branch n (insert x l) r


findTreeDFS :: Eq a => a -> Tree a -> Tree a
findTreeDFS _ Empty = Empty
findTreeDFS x (Leaf a)         = if a == x then (Leaf a) else Empty
findTreeDFS x t@(Branch a l r) = 
    if a == x 
        then t 
        else let fl = findTreeDFS x l in
             if fl /= Empty then fl
               else findTreeDFS x r               

                 
testTree :: Tree Integer
testTree = Branch 8 (Branch 4 (Leaf 3) (Leaf 5)) (Branch 9 Empty (Leaf 10))


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