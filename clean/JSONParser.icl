implementation module JSONParser

import Parsers
import StdEnv
import StdLib

// 1. Introduction

:: Value = JString String
         | JNumber Real
	 | JBoolean Bool
	 | JNull
	 | JArray [Value]
	 | JObject [(String, Value)]

// 2. JSON Grammar

json_text = object <!> array

// Structural characters
begin_array	= ws &> symbol '[' <& ws
begin_object	= ws &> symbol '{' <& ws
end_array	= ws &> symbol ']' <& ws
end_object	= ws &> symbol '}' <& ws
name_separator	= ws &> symbol ':' <& ws
value_separator = ws &> symbol ',' <& ws

// Insignificant whitespace
ws = <!*> ( symbol ' '
           <!> symbol '\t'
           <!> symbol '\n'
           <!> symbol '\r'
         )

// 2.1 Value

value = false <!> null <!> true <!> object <!> array <!> js_number <!> js_string

false = lit "false" &> yield (JBoolean False)
null  = lit "null"  &> yield (JNull)
true  = lit "true"  &> yield (JBoolean True)

// 2.2 Objects

object = begin_object &> (empty_object <!> non_empty_object)
  where
    empty_object     = end_object &> yield (JObject [])
    non_empty_object = (JObject @> sepBy value_separator member) <& end_object

member = (string <& name_separator) <&&> value

// 2.3 Arrays
array = first (begin_array &> (empty_array <!> non_empty_array))
  where
    empty_array     = end_array &> yield (JArray [])
    non_empty_array = (JArray @> sepBy value_separator value) <& end_array

// 2.4 Numbers

js_number = JNumber @> (
  (minus &> yield (~) <!> yield id)
  <++>
  (sumall @> (int <&&> (frac <!> yield 0.0) <&&> (exp` <!> yield 1.0))))
  where
    sumall (i, (f, e)) = (toReal i + f) * e

decimal_point = symbol '.'

digit1_9 = satisfy (\c -> isMember c ['1'..'9']) <@ digitToInt

e = symbol 'e' <!> symbol 'E'

exp` = e &> (sign <++> (DIGIT1 <@ (\n -> toReal (10 ^ n))))
  where
    sign =  minus &> yield (\c -> 1.0 / c)
        <!> plus  &> yield id
        <!> yield id

frac = decimal_point &> (<!+> digit) <@ snd o foldl go (10.0,0.0)
  where
    go (n, acc) d = (n * 10.0, acc + toReal (digitToInt d) / n )

int = zero` <!> ((digit1_9 <:&> (<!*> (toInt @> digit))
                    <@ (toReal o foldl (\n d -> 10 * n + d) 0)))

DIGIT1 = (<!+> digit) <@ foldl (\n d -> 10*n + digitToInt d) 0

minus = symbol '-'
plus  = symbol '+'
zero`  = symbol '0' &> yield 0.0

// 2.5 Strings (incomplete and buggy)
// Unicode are not corretly handled, I'm too lazy to write a utf-8 parser

js_string = JString @> string

string = quotation_mark &> (toString @> (<*> (escaped <!> unescaped)))
         <& quotation_mark

escape = symbol '\''

escaped = escape &> (
      esc '\"' '\"'
  <!> esc '\\' '\''
  <!> esc '/'  '/'
  <!> esc 'b'  '\b'
  <!> esc 'f'  '\f'
  <!> esc 'n'  '\n'
  <!> esc 'r'  '\r'
  <!> esc 't'  '\t')
  where esc c s = symbol c &> yield s

quotation_mark = symbol '"'

unescaped :: Parser Char Char a
unescaped = satisfy is_unescaped
  where
   is_unescaped c =
      let i = toInt c
      in (i == 0x20 || i == 0x21
          || (i >= 0x23 && i <= 0x5B)
          || (i >= 0x5D && i <= 0x10FFFF))

// Helpers

lit :: String -> Parser Char [Char] a
lit str = str :> token (fromString str)

sepBy sep p = p <:&> (<!*> (sep &> p))

// Exported funtion
parseJSON :: String -> Maybe Value
parseJSON str =
   case parse json_text (fromString str) "" "" of
     Succ [r:rs] -> Just r
     Err _ _ _   -> Nothing

// Main
Start world
  # (console, world) = stdio world
    (input, console) = freadline console
  = parseJSON input
