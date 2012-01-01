module Main where

main :: IO ()
main = putStrLn $ unwords $ map fizzbuzz'' [-50, -49 .. 50]

fizzbuzz :: [Int] -> [String]
fizzbuzz [] = []
fizzbuzz (x:xs)
    | x `rem` 3 == 0 && x `rem` 5 == 0 = "FizzBuzz" : fizzbuzz xs
    | x `rem` 3 == 0 = "Fizz" : fizzbuzz xs
    | x `rem` 5 == 0 = "Buzz" : fizzbuzz xs
    | otherwise = show x : fizzbuzz xs


fizzbuzz' :: Int -> [String] -> [String]
fizzbuzz' x result
    | x `rem` 3 == 0 && x `rem` 5 == 0 = "FizzBuzz" : result
    | x `rem` 3 == 0 = "Fizz" : result
    | x `rem` 5 == 0 = "Buzz" : result
    | otherwise = show x : result

fizzbuzz'' :: Int -> String
fizzbuzz'' n
    | divisibleyBy3 && divisibleyBy5 = "FizzBuzz"
    | divisibleyBy3 = "Fizz"
    | divisibleyBy5 = "Buzz"
    | otherwise = show n
  where
    divisibleyBy3 = n `rem` 3 == 0
    divisibleyBy5 = n `rem` 5 == 0