import System.IO
import System.Environment
import Data.List

type FreqTable a = [(a, Int)]
type WordFreqTable = FreqTable String

main =
  getArgs
  >>= (\arg -> readFile $ arg !! 0)
  >>= (\f -> return $ words f)
  >>= (\x -> printWordFreq $ take 10 $sortFreq $ countFreq x)

countFreq :: (Eq a , Ord a) => [a] -> FreqTable a
countFreq words =
  map count $ group $ sort words
  where count [x] = (x, 1)
        count (x:xs) = (x, 1 + snd (count xs))

sortFreq :: FreqTable a -> FreqTable a
sortFreq freqs =
  sortBy rule freqs
  where rule x y =
          case (snd x) > (snd y) of
            True -> LT
            otherwisw -> GT

printWordFreq :: WordFreqTable -> IO [()]
printWordFreq freqs = do
  mapM (\f -> do
           putStr $fst f ++ "\t"
           putStrLn $ show $snd f) freqs