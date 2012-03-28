module Main where

import Text.ParserCombinators.Parsec hiding (spaces)
import System.Environment
import Control.Monad
import Numeric

data LispVal = Atom String
             | List [LispVal]
             | DottedList [LispVal] LispVal
             | Number Integer
             | String String
             | Char Char
             | Float Float
             | Bool Bool

symbol :: Parser Char
symbol = oneOf "!#$%&|*+-/:<=>?@^_~"

spaces :: Parser ()
spaces = skipMany1 space

parseString :: Parser LispVal
parseString = do 
    char '"'
    x <- many (escapedChar <|> noneOf "\"")
    char '"'
    return $ String x

escapedChar :: Parser Char
escapedChar =  do
    char '\\' 
    c <- oneOf "nrt\\\""
    let ec =  case c of
                'n'  -> '\n'
                't'  -> '\t'
                '\\' -> '\\'
                '\"' -> '\"'
    return c

parseAtom :: Parser LispVal
parseAtom = do
    first <- letter <|> symbol
    reset <- many (letter <|> digit <|> symbol)
    let atom = first : reset
    return $ case atom of
               "#t" -> Bool True
               "#f" -> Bool False
               _    -> Atom atom

parseNumber :: Parser LispVal
parseNumber = try parseNormalDecNumber <|>
              try parseBinNumber <|>
              try parseOctNumber <|>
              try parseDecNumber <|>
              parseHexNumber

parseBinNumber :: Parser LispVal
parseBinNumber = do
    char '#' >> char 'b'
    bin <- many1 (oneOf "01")
    return $ Number $ read bin

parseOctNumber :: Parser LispVal
parseOctNumber = do
    char '#' >> char 'o'
    str <- many1 (oneOf "01234567")
    let (oct, _) = (head . readOct) str
    return $ Number oct

parseHexNumber :: Parser LispVal
parseHexNumber = do
    char '#' >> char 'x'
    str <- many1 (oneOf "0123456789abcedfABCDEF")
    let (hex, _) = (head . readHex) str
    return $ Number hex

parseDecNumber :: Parser LispVal
parseDecNumber = do
    char '#' >> char 'd'
    str <- many1 (oneOf "0123456789")
    return $ (Number . read) str


parseNormalDecNumber :: Parser LispVal
parseNormalDecNumber = liftM (Number . read) $ many1 digit

parseExpr :: Parser LispVal
parseExpr = parseAtom <|> parseString <|> parseNumber

readExpr :: String -> String
readExpr input =
    case parse parseExpr "lisp" input of
      Left err -> "No match: " ++ show err
      Right _ -> "Found value"

main :: IO ()
main = do
    (args:_) <- getArgs
    putStrLn $ readExpr args

{--
readExpr :: String -> String
readExpr input = 
    case parse (space >> symbol) "lisp" input of
      Left err -> "No match: " ++ show err
      Right val -> "Found value"
--}