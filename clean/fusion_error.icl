module fusion_error

import StdEnv

f ls p = map (p o snd) ls

// Comment out `evil` and everything will be fine
evil = f [(1,1)] isOdd

ok = f [(1,1)] (\c -> isOdd c)

Start = "Compile with -fusion"
