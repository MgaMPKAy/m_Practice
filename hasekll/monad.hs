(//) :: Maybe Float -> Maybe Float -> Maybe Float
x // y =
  do
    x <- x
    y <- y
    if b == 0 then Nothing else Just (a / b)
