{-# LANGUAGE ExistentialQuantification #-}
module ForAll where

data ShowBox = forall s . Show s => SB s

instance Show ShowBox where
    show (SB s) = show s

main :: IO ()
main = mapM_ putStrLn $ map show [SB 'a', SB "b", SB (), SB 1]