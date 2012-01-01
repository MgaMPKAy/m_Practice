module Main where

data Door = Opened | Closed deriving Show

toggle :: Door -> Door
toggle Opened = Closed
toggle Closed = Opened


toggleEvery :: [Door] -> Int -> [Door]
toggleEvery doors n = snd $ foldl f (1, []) doors
  where
    f (i, r) door
      | i `rem` n == 0 = (i + 1, r ++ [toggle door]) -- bad proformance
      | otherwise = (i + 1, r ++ [door])


main :: IO ()
main = mapM_ (putStrLn . show) $ foldl toggleEvery (replicate 100 Closed) [1..100]

