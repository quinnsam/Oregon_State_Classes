module HW2 where

-- Authors Sam Quinn, Anton Dovzhik

-- ** Exercise 1. A Rank-Based Type for the Stack Language **

type Prog       = [Cmd]
type Stack      = [Int]
type D          = (Stack -> Stack)

type Rank       = Int
type CmdRank    = (Int, Int)

data Cmd = LD Int
         | ADD
         | MULT
         | DUP
         | INC
         | SWAP
         | POP Int
         deriving (Show)

-- A
-- rankC maps each stack operation to its rank
rankC :: Cmd -> CmdRank
rankC ADD     = (2,1)
rankC MULT    = (2,1)
rankC DUP     = (1,2)
rankC INC     = (1,1)
rankC SWAP    = (2,2)
rankC (POP x) = (x,0)
rankC (LD _)  = (0,1)

-- rank is an auxiliary function that calls rankC
rank :: Prog -> Rank -> Maybe Rank
rank [] c       = Just c
rank (o:os) c 
        | c >= rc = rank os (c - rc + rr)
        | otherwise = Nothing
        where (rc, rr) = (rankC o)

-- Computes the rank of a function
rankP :: Prog -> Maybe Rank
rankP []    = Just 0
rankP os    = rank os 0

-- B

-- We can use the type checker to perform only safe evaluations
typeSafe :: Prog -> Bool
typeSafe e = rankP e /= Nothing

semStatTC :: Prog -> Stack -> Maybe Stack
semStatTC es e  | typeSafe es = Just (sem es e)
    | otherwise  = Nothing

-- Functions from HW #2
semCmd :: Cmd -> D
semCmd (LD i) s          = (i:s)
semCmd DUP    vs@(v:_)   = (v:vs)
semCmd ADD    (v1:v2:vs) = (v1+v2:vs)
semCmd MULT   (v1:v2:vs) = (v1*v2:vs)
-- Added new functions for HW #3
semCmd INC    (v:vs)     = (v+1:vs)
semCmd SWAP   (v1:v2:vs) = (v2:v1:vs)
semCmd (POP 0) (vs)      = (vs) 
semCmd (POP i) (v:vs)    = semCmd (POP (i-1)) vs

-- Sematics function
sem :: Prog -> D
sem []     c  = c
sem (o:os) c  = sem os (semCmd o c)

-- TEST CASES --
-- Returns correct ranks
c1 = semStatTC [LD 1, LD 9, SWAP, ADD] []
c2 = semStatTC [LD 2, LD 4, LD 5, POP 1, MULT] []
c3 = semStatTC [LD 5, DUP, DUP, DUP, SWAP, POP 2] []

-- Returns Nothing, Errors
e1 = semStatTC [LD 3, LD 4, LD 6, POP 2, ADD] []
e2 = semStatTC [LD 3, SWAP] []
e3 = semStatTC [DUP] []


