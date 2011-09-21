import Data.IORef

data Tree a = Leaf a | Branch (Tree a, Tree a) deriving Show

tree :: Tree String
tree =
  Branch (Leaf "Max",
          Branch (Leaf "Bernd",
                  Branch (
                    Branch (
                       Leaf "Holger",
                       Leaf "Ralf"),
                    Branch (
                      Leaf "Kerstin",
                      Leaf "Steffen"))))

printTree :: Show a => Tree a -> IO()
printTree t = printTL t 0
  where printTL t level = do
          let indent = replicate (level * 2) ' '
          case t of
            Leaf l -> putStrLn $ indent ++ "Leaf: " ++ show l
            Branch (left, right) -> do
              putStrLn $ indent ++ "Branch:"
              printTL left (level + 1)
              printTL right (level + 1)


labalTreeS1 :: Tree a -> IO (Tree (a, Int))
labalTreeS1 tree =  do
  count <- newIORef 1
  labalTL tree count
  where labalTL tree cref =
          case tree of
            Leaf leaf -> do
              c <- readIORef cref
              writeIORef cref (c + 1)
              return $ Leaf (leaf, c)
            Branch (left, right) -> do
              newLeft <- labalTL left cref
              newRight <- labalTL right cref
              return $ Branch (newLeft, newRight)

labalTreeS2 t = fst $ labalTreeNM t 1
  where labalTreeNM t s =
          case t of
            Leaf leaf -> (Leaf (leaf, s), s + 1)
            Branch (left, right) ->
              let (newLeft, sl) = labalTreeNM left s
                  (newRight, sr) = labalTreeNM right sl in
              (Branch (newLeft,newRight), sr)
