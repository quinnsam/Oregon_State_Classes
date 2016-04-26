module List2 where

import Test
import Data.List (nub)
default (Int)


exch :: [a] -> [a]
exch (x:y:xs) = y:x:xs
exch xs       = xs     -- leave lists with fewer than 2 elems unchanged


selMin :: Ord a => [a] -> a
selMin [x]   = x
-- selMin (x:xs) | selMin xs < x = selMin xs
--               | otherwise     = x
selMin (x:xs) | m < x     = m
              | otherwise = x
                where m = selMin xs


bubble :: Ord a => [a] -> (a,[a])
bubble [x]    = (x,[])
bubble (x:xs) | m < x     = (m,x:ys)
              | otherwise = (x,m:ys)
                where (m,ys) = bubble xs

-- splitVal fails if x is not an element of the list
splitVal :: Eq a => a -> [a] -> (a,[a])
splitVal x (y:xs) | x==y      = (x,xs)
                  | otherwise = (x,y:ys)
                    where (_,ys) = splitVal x xs

splitMin :: Ord a => [a] -> (a,[a])
splitMin xs = splitVal (selMin xs) xs


test = TestSuite "splitMin" 
        [[4]         ==> (4,[]),
         [6,4,5]     ==> (4,[6,5]),
         [7,3,6,4,5] ==> (3,[7,6,4,5])]

res1 = runTest bubble test
res2 = runTest splitMin test


selSort :: Ord a => [a] -> [a]
selSort [] = []
selSort xs = m:selSort ys
             where (m,ys) = splitMin xs


divisors :: Int -> [Int]
divisors n = [m | m <- [2 .. n `div` 2], n `mod` m==0]
-- divisors n = [m | m <- [2 .. div n 2], mod n m==0]


prime :: Int -> Bool
prime n = divisors n==[]


type Rel a = [(a,a)]

r :: Rel Int
r = [(1,2),(2,3),(2,5),(3,4)]


dom :: Eq a => Rel a -> [a]
dom r = nub [x | (x,y) <- r]
-- dom r = nub [x | (x,_) <- r]
-- dom r = nub (map fst r)
-- dom = nub . map fst

rng :: Eq a => Rel a -> [a]
rng = nub . map snd


comp :: Eq a => Rel a -> Rel a -> Rel a
comp r s = nub [(x,z) | (x,y) <- r, (a,z) <- s, y==a]


-- data Node = N Int
type Node = Int
type Graph = Rel Node
type Path = [Node]


suc :: Graph -> Node -> [Node]
suc g v = [w | (x,w) <- g, v==x]

paths :: Graph -> Node -> Node -> [Path]
paths g v w | v==w      = [[v]]
            | otherwise = [ v:p | u <- suc g v, p <- paths g u w] 


