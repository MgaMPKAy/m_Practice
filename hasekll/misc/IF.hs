module IF where

data Then = Then
data Else = Else
data If a = If Bool Then a Else a

evalIf :: If a -> a
evalIf (If p Then a Else b)
    | p = a
    | otherwise = b

main :: IO ()
main = print $ evalIf $ If (1 > 0) Then (1 + 1) Else (0)
