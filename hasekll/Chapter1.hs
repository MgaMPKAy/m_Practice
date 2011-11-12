module Chapter1 where

-- 1.3
max_of_three :: Ord a => a -> a -> a -> a
max_of_three a b c = max a $ max b c



-- 1.5
p :: t
p = p

test x y =
    if x == 0 then 0 else y

-- 1.6
new_if :: Bool -> t -> t -> t
new_if predicate then_clause else_clause
       | predicate = then_clause
       | otherwise = else_clause

-- 1.7

-- 1.8

-- 1.10
ackermann :: Int -> Int -> Int
ackermann x y
    | y == 0 = 0
    | x == 0 = 2 * y
    | y == 1 = 2
    | otherwise = ackermann (x - 1) (ackermann x (y - 1))

-- 1.11
func n
    | n < 3 = n
    | n >= 3 = func (n - 1) + 2 * func (n - 2) + 3 * func (n - 3)

-- func' n

-- 1.12
pasca n b
      | b == 1 = 1
      | n == b = 1
      | otherwise = pasca (n - 1) b + pasca (n - 1) (b - 1)

count_change :: Int -> [Int] -> Int
count_change amount kinds
    | amount == 0 = 1
    | amount < 0 || length kinds == 0 = 0
    | otherwise = count_change amount (tail kinds) + 
                  count_change (amount - (head kinds)) kinds