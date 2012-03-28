subsequences' :: [a] -> [[a]]
subsequences' [] = [[]]
subsequences' (x:xs) =  subs ++ map (x:) subs
  where subs = subsequences' xs

