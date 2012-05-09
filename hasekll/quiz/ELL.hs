module ELL where

import Data.List
import Text.ParserCombinators.Parsec

data Maou
    = Plain String
    | A
    | B
    | Paren [Maou]
    deriving (Eq, Show)

type MaouLang = [Maou]

parseA :: Parser MaouLang
parseA = char 'A' >> return [A]

parseB :: Parser MaouLang
parseB = char 'B' >> return [B]

parsePlain :: Parser MaouLang
parsePlain =  many (noneOf "AB()") >>= (return . (:[]) . Plain)

parseParen :: Parser MaouLang
parseParen = do
    char '('
    maou <- parseMaou
    char ')'
    return $ [Paren maou]

parseMaou :: Parser MaouLang
parseMaou = do
    x <- parseA <|> parseB <|> parsePlain <|> parseParen
    xs <- parseMaou
    return (x ++ xs)


{--
decode ruleB ruleA input = fst $ foldl step ([], 0) (input ++ ['#'])
  where
    step (stack, count) c
        | c == 'A'  = (reverse ruleA ++ stack, count)
        | c == 'B'  = (reverse ruleBA ++ stack, count)
        | c == '('  = ([c] ++ stack, count + 1)
        | c == ')'  = let h = takeWhile (/='(') stack
                          t = drop 1 $ dropWhile (/='(') stack
                      in (reverse (rule2 h) ++ t, count - 1)
        | c == '#'  = (reverse stack, count)
        | otherwise = ([c] ++ stack, count)

    ruleBA = concatMap (\x -> if x == 'A' then ruleA else [x]) ruleB
--}

decode' ruleB ruleA input =
    replace 'A' ruleA $ replace 'B' ruleB $
            fst $ foldl step ([], 0) (input ++ ['#'])
  where
    step (stack, count) c
        | count < 0 = error "( and ) not matched"
        | c == '('  = ([c] ++ stack, count + 1)
        | c == ')'  = let h = takeWhile (/='(') stack
                          t = drop 1 $ dropWhile (/='(') stack
                      in
                        (reverse (rule2 h) ++ t, count - 1)
        | c == '#'  = if (count /= 0)
                          then error "( and ) not matched"
                          else (reverse stack, count)
        | otherwise = ([c] ++ stack, count)

    replace c str = concatMap (\x -> if x == c then str else [x])

rule2 [] = []
rule2 [x] = [x]
rule2 l = (last l) : intersperse (last l) (init l) ++ [last l]


showELL str = concatMap preety str
  where
    preety 't' = "天"
    preety 'd' = "地"
    preety 's' = "上"
    preety 'a' = "一只"
    preety 'e' = "鹅"
    preety 'z' = "追"
    preety 'g' = "赶"
    preety 'x' = "下"
    preety 'n' = "蛋"
    preety 'h' = "恨"
    preety  x  = [x]

example = putStrLn $ showELL $ decode' "tAdA" "sae" "B(ehnxgz)B"