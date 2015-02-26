module HW2 where

-- Authors Sam Quinn, Anton Dovzhik

-- ** Exercise 1. A Stack Language **

type Prog       = [Cmd]
type Stack      = [Int]
type D          = Maybe Stack -> Maybe Stack

data Cmd = LD Int
         | ADD
         | MULT
         | DUP
         deriving (Show)


semCmd :: Cmd -> D
semCmd (LD i) (Just s)          = Just (i:s)
-- @ grabs everything in the list including the first character.
semCmd DUP    (Just vs@(v:_))   = Just (v:vs)
semCmd ADD    (Just (v1:v2:vs)) = Just (v1+v2:vs)
semCmd MULT   (Just (v1:v2:vs)) = Just (v1*v2:vs)
semCmd _      _                 = Nothing

sem :: Prog -> D
sem []     c  = c
sem (o:os) c  = sem os (semCmd o c)

-- ** Exercise 2. Digital Circuit Design Language **

