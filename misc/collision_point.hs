power_func f x n
  | n == 0 = x
  | otherwise = power_func f (f x) (n - 1)

collision_point f x =
  cp_helper x (f x)
    where cp_helper slow fast
            | slow == fast = fast
            | otherwise = cp_helper f (f slow) (f $ f fast)

-- Test
list :: [Int]
list = [1,2,3,4,5,2]
func n = list !! (n `rem` 5)
a = collision_point func 1
b = collision_point func 2