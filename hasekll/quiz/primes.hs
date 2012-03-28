primes [] = []
primes (x:xs) =
  x : primes (filter (\n -> n `rem` x /= 0) xs)

main = do
  return (show $ take 1000 $ primes [2..]) >>= putStrLn
