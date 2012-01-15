module Fraction where

import Text.ParserCombinators.Parsec

data Fraction = Fraction Int Int

instance Show Fraction where
    show (Fraction n m)
        | m == 0 = error "divided by zero"
        | n == 0 = "0"
        | otherwise = show n ++ "/" ++ show m

instance Read Fraction where
    readsPrec _ = readFraction

fractionParser :: Parser Fraction
fractionParser = do
    spaces <|> skipMany spaces
    n <- many digit
    spaces <|> skipMany spaces
    char '/'
    spaces <|> skipMany spaces
    m <- many digit
    spaces <|> skipMany spaces
    return $ case (read m) of
               0 -> error "divided by zero"
               mm -> Fraction (read n) mm

parseFraction :: String -> Fraction
parseFraction str = 
    case parse fractionParser "" str of
      Left  _ -> error "parse error"
      Right f -> f

readFraction :: ReadS Fraction
readFraction str = [(parseFraction str, "")]

addFraction :: Fraction -> Fraction -> Fraction
addFraction (Fraction n1 m1) (Fraction n2 m2) =
    simpilify $ Fraction (n1 * m2 + n2 * m1) (m2 * m1)

subFraction :: Fraction -> Fraction -> Fraction
subFraction (Fraction n1 m1) (Fraction n2 m2) =
    simpilify $ Fraction (n1 * m2 - n2 * m1) (m2 * m1)

mulFraction :: Fraction -> Fraction -> Fraction
mulFraction (Fraction n1 m1) (Fraction n2 m2) =
    simpilify $ Fraction (n1 * n2) (m2 * m1)

divFraction :: Fraction -> Fraction -> Fraction
divFraction (Fraction n1 m1) (Fraction n2 m2) =
    simpilify $ Fraction (n1 * m2) (m1 * n2)

simpilify :: Fraction -> Fraction
simpilify (Fraction n m) = Fraction (n `div` g) (m `div` g)
  where g = gcd n m
