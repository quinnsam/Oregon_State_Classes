module TypeCheck where

data Expr = N Int
          | Plus Expr Expr
          | Equal Expr Expr
          | Not Expr
          deriving Show

data Type = Int | Bool | TypeError
          deriving (Eq, Show)

data Val = I Int | B Bool
         deriving Show

int :: Val -> Int
int (I i) = i
int v     = error ("Value "++show v++" is not an integer")

bool :: Val -> Bool
bool (B b) = b
bool v     = error ("Value "++show v++" is not a boolean")

tc :: Expr -> Type
tc (N i)                                    = Int
tc (Plus e e')  | tc e==Int && tc e'==Int   = Int
tc (Equal e e') | tc e==Bool && tc e'==Bool = Bool
                | tc e==Int && tc e'==Int   = Bool
tc (Not e)      | tc e==Bool                = Bool
tc _                                        = TypeError

eval :: Expr -> Val
eval (N i)  = I i
eval (Plus x y) = I (int x'+int y') where (x',y') = (eval x, eval y)
eval (Equal x y) = B (int x'==int y') where (x',y') = (eval x, eval y)
eval (Not x)    = B (not (bool x')) where (x') = (eval x)

typeSafe :: Expr -> Bool
typeSafe e = tc e /= TypeError


evalStatTC :: Expr -> Maybe Val
evalStatTC e | typeSafe e = Just (eval e) 
             | otherwise = Nothing


xs = [1,2,3]
ys = [4,5]
zs = [6]
ll = [xs,ys,zs]

f :: [a] -> [a]
f xs = f' xs []
f' [] ys = ys
f' (x:xs) ys = f' xs (x:ys)

g :: [a] -> [a] -> [a]
g [] ys = ys
g (x:xs) ys = x:g xs ys


h (x:y:xs) = y:h (x:xs)
h _ = []

