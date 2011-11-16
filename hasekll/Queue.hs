module Queue 
    (
     newQueue,
     add,
     isEmpty,
     remove,
     size,
    )
where

data Queue a = Queue [a]

newQueue :: Queue a
newQueue = Queue []

add :: a -> Queue a -> Queue a
add e (Queue q) = Queue $ q ++ [e]

isEmpty :: Queue a -> Bool
isEmpty (Queue q) = null q

remove :: Queue a -> (a, Queue a)
remove (Queue q) = (head q, Queue $ tail q)

size :: Queue a -> Int
size (Queue q) = length q

