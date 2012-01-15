module Main where

import Text.ParserCombinators.Parsec
import System.Environment
import Control.Monad

data Type = Idea | Todo | Done deriving Show

data Item = Item Type String

instance Show Item where
    show (Item t deatil) = show t ++ ":" ++ deatil

parseType :: Parser Type
parseType = do 
    c <- oneOf "ITD"
    return $ case c of
              'I' -> Idea
              'T' -> Todo
              'D' -> Done

parseItem :: Parser Item
parseItem = do
    t <- parseType
    char ':'
    s <- many anyChar
    return $ Item t s

main :: IO ()
main = do
    (file:_) <- getArgs
    content <- readFile file
    let result = map (parse parseItem "Item") (lines content)
    mapM_ print result