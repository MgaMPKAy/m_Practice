module segfault2

import StdFile

Start world = world3
  where
    (_, file1, world2) = fopen "file"  FReadText world
    (_, file2, world3) = fopen "file"  FWriteText world2
