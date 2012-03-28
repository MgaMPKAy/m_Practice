module User where

import qualified Data.Map as M
import Control.Applicative

cache :: M.Map Integer Integer
cache = M.fromList [(1, 1)]

db :: M.Map Integer Integer
db = M.fromList [(1,1)]

getCacheUser :: Integer -> Integer -> Maybe Integer
getCacheUser id0 name =
   getUserById cache id0
   <|> getUserByName cache name
   <|> getUserById cache id0
   <|> getUserByName db id0

getUserById :: Ord k => M.Map k a -> k -> Maybe a
getUserById _cache _id = M.lookup _id _cache

getUserByName :: Ord k => M.Map k a -> k -> Maybe a
getUserByName _cache _id = M.lookup _id _cache