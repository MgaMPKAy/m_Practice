module Stack 
    (
     newStack,
     isEmpty,
     peek,
     pop,
     push,
     size,
    )
where

data Stack a = Stack [a]

newStack :: Stack a
newStack = Stack []

isEmpty :: Stack a -> Bool
isEmpty (Stack s) = null s

peek :: Stack a -> a
peek (Stack s) = head s

pop :: Stack a -> (a, Stack a)
pop (Stack s) = (head s, Stack $ tail s)

push :: a -> Stack a -> Stack a
push e (Stack s) = Stack $ e : s

size :: Stack a -> Int
size (Stack s) = length s