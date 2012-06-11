module Parser (parse) where

import Types
import Control.Monad.State

type ParserState = State [Token]

parse :: [Token] -> Prop
parse = evalState parse'

parse' :: ParserState Prop
parse' = do
    prop <- parseProp
    tk <- currentToken
    case tk of
      End -> return prop
      _   -> error "parser error"

parseProp :: ParserState Prop
parseProp = do
    exp <- parseExp
    tk   <- currentToken
    case tk of
      OpOr -> do
          advnaceToken
          prop <- parseProp
          return $ POr exp prop
      _ -> return $ PExp exp


parseExp :: ParserState Exp
parseExp = do
    term <- parseTerm
    tk   <- currentToken
    case tk of
      OpAnd -> do
          advnaceToken
          exp <- parseExp
          return $ EAnd term exp
      _ -> return $ ETerm term


parseTerm :: ParserState Term
parseTerm = do
    tk <- currentToken
    case tk of
      Var name -> advnaceToken >> (return $ TVar name)
      LeftParen -> do
          advnaceToken
          prop <- parseProp
          tk   <- currentToken
          case tk of
            RightParen -> advnaceToken >> (return $ TParen prop)
            _          -> error "paren not match"
      OpNot -> do
          advnaceToken
          prop <- parseProp
          return $ TNot prop


currentToken :: ParserState Token
currentToken = get >>= return . head

advnaceToken :: ParserState ()
advnaceToken = modify (drop 1)
