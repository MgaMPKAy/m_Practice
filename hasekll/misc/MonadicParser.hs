{-# LANGUAGE MonadComprehensions #-}
module MonadicParser where

import Control.Monad

newtype Parser a = Parser (String -> [(a, String)])

instance Monad Parser where
    return = result
    (>>=)  = bind

instance MonadPlus Parser where
    mzero = zero
    mplus = plus

result :: a -> Parser a
result v = Parser $ \inp -> [(v, inp)]

zero :: Parser a
zero = Parser $ \_ -> []

item :: Parser Char
item = Parser $ \inp -> 
       case inp of
         "" -> []
         (c:cs) -> [(c, cs)]

bind :: Parser a -> (a -> Parser b) -> Parser b
p `bind` f = 
    Parser $ \inp -> concat [parse (f v) inp' | (v, inp') <- parse p inp]

parse :: Parser a -> (String -> [(a, String)])
parse (Parser p) = p


sat :: (Char -> Bool) -> Parser Char
sat p = do
    x <- item
    if p x
       then return x
       else mzero

char :: Char -> Parser Char
char x = sat (\y -> x == y)

digit :: Parser Char
digit = sat (\x -> '0' <= x && x <= '9')

lower :: Parser Char
lower = sat (\x -> x `elem` ['a'..'z'])

upper :: Parser Char
upper = sat (\x -> 'A' <= x && x <= 'Z')

plus :: Parser a -> Parser a -> Parser a
p `plus` q = Parser $ \inp -> (parse p inp ++ parse q inp)

letter :: Parser Char
letter = lower `mplus` upper

alphanum :: Parser Char
alphanum = letter `mplus` digit

word :: Parser String
word = neWord `mplus` return ""
  where
    neWord = letter >>= \c ->
             word   >>= \cs ->
             return (c:cs)

string :: String -> Parser String
string "" = return ""
string (c:cs) = char c >> string cs >> return (c:cs)

stringmc :: String -> Parser String
stringmc "" = return ""
stringmc (c:cs) = [(c:cs) | _ <- char c, _ <- stringmc cs]

satmc :: (Char -> Bool) -> Parser Char
satmc p = [x | x <- item, p x]

satdo :: (Char -> Bool) -> Parser Char
satdo p = do
    x <- item
    if p x then return x else mzero

wordmc :: Parser String
wordmc = [c:cs| c <- letter, cs <-wordmc] `mplus` (return "")

many :: Parser a -> Parser [a]
many p = (p >>= \x -> many p >>= \xs -> return (x:xs)) `mplus` return []

manymc :: MonadPlus m => m a -> m [a]
manymc p = [x:xs | x <- p, xs <- manymc p] `mplus` return []

ident :: Parser String
ident = letter >>= \x -> many alphanum >>= \xs -> return (x:xs)

many1 :: Parser a -> Parser [a]
many1 p = p >>= \x -> many p >>= \xs -> return (x:xs)

nat :: Parser Int
nat = do
    n <- many1 digit
    return $ read n
--    where eval xs = foldl1 op [read [x] | x <- xs]
--          m `op` n = 10 * m + n

int :: Parser Int
int = (char '-' >> nat >>= return . negate) `mplus` nat

int' :: Parser Int
int' = do
    f <- op
    n <- nat
    return $ f n
  where op = (char '-' >> return negate) `mplus` return id