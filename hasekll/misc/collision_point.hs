powerFunc f x n
  | n == 0 = x
  | otherwise = powerFunc f (f x) (n - 1)

collisionPoint f x =
  cpHelper x (f x)
    where cpHelper slow fast
            | slow == fast = fast
            | otherwise = cpHelper f (f slow) (f $ f fast)

-- Test
list :: [Int]
list = [1,2,3,4,5,2]
func n = list !! (n `rem` 5)
a = collisionPoint func 1
b = collisionPoint func 2