> {-# LANGUAGE OverloadedStrings #-}

> module Result where

> import Data.Aeson.Types hiding (Result)
> import Yesod.Json(array)

> data Result a = Result Status [a]
> type Status = String

> instance (ToJSON a) => ToJSON (Result a) where
>     toJSON (Result status xs) =
>         object $ [ "status" .= status
>                  , "data" .= array xs
>                  ]

> data XY = XY Int Int
> instance ToJSON XY where
>     toJSON (XY x y) = object ["x" .= x, "y" .= y ]
