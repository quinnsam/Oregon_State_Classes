module Test where


das :: [Int] -> [Int]
das vs@(v:_) = (v:vs)
