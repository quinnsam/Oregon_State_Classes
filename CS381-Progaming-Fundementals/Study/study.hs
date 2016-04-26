module Study where

import Prelude hiding (succ, pred)


xs = [1,2,3]
ys = [4,5]
zs = [6]
ll = [xs,ys,zs]

maxl :: [Int] -> Int
maxl [x] = x
maxl (x:y:xs) = maxl (max x y : xs)

g :: [Int] -> [Int]
g (x:y:xs) = y:g (x:xs)
g _ = []

data Nat = Zero 
         | Succ Nat
         deriving(Eq, Show)


one = Succ Zero
two = Succ one
three = Succ two

pred :: Nat -> Nat
pred Zero = Zero
pred (Succ n) = n


isZero :: Nat -> Bool
isZero Zero = True
isZero _ = False


add :: Nat -> Nat -> Nat
add Zero m = m
add (Succ x) y  = Succ (add x y)


equal :: Nat -> Nat -> Bool
equal Zero Zero = True
equal (Succ x) (Succ y) = equal x y
equal _ _ = False

gt :: Nat -> Nat -> Bool
gt Zero Zero = False
gt _ Zero = True
gt (Succ x) (Succ y) = gt x y
gt Zero _ = False

mult :: Nat -> Nat -> Nat
mult Zero _ = Zero
mult (Succ x)  y = add y (mult x y)


data Digit = O | I
           deriving (Eq, Show)


data Bin = Single Digit
         | Comp Digit Bin

instance Show Bin where
    show (Single d) = show d
    show (Comp d b) = show d ++ show b

sucC :: Bin -> (Digit, Bin)
sucC (Single O) = (O, Single I)
sucC (Single I) = (I, Single O)
sucC (Comp O xs) = (I, Comp c xs)
                    where (c, xs) = sucC xs
sucC (Comp I xs) = (O, Comp c xs)
                    where (c, xs) = sucC xs


--data Sentence = Phrase Noun Verb Noun
--              | And Sentance Sentance
--              deriving Show
--
--data Noun = dogs | teeth
--
--data Verb = have

data BExpr = T | F | Not BExpr
           | Or BExpr BExpr
           | And BExpr BExpr
           deriving Show

sem :: BExpr -> Bool
sem T = True
sem F = False
sem (Not x) = not (sem x)
sem (Or x y) = (sem x) || (sem y)
sem (And x y) = (sem x) && (sem y)

