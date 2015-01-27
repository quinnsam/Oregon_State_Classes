module HW1 where

-- ** Exercise 1. Mini Logo **
-- a) Define the abstract syntax for Mini Logo as a Haskell data type.
-- b) Write a Mini Logo macro vector that draws a line from a given position (x1, y1)
--    to a given position (x2, y2) and represent  the macro in abstract syntax, that 
--    is, as a Haskell data type value.
-- c) Define a Haskell function steps :: Int -> Cmd that constructs a Mini Logo program
--    which draws a stair of n steps. 

-- A
type Name = String
type Number = Int
type Position = (Pos, Pos)

data Cmd = Pen Mode
         | Moveto Position 
         | Def Name Pars Cmd
         | Call Name Vals 
         | Clist [Cmd]
         deriving Show

data Mode = Up | Down deriving Show
data Pos  = Pos_Int Number | Pos_String Name deriving Show
data Pars = Plist [Name] deriving Show
data Vals = Vlist [Number] deriving Show

-- B
vector = Def "vector" (Plist ["x1", "y1", "x2", "y2"]) (Clist [(Pen Up), (Moveto (Pos_String "x1", Pos_String "y1")), (Pen Down), (Moveto(Pos_String "x2", Pos_String "y2")), (Pen Up)])

return = Call "vector" (Vlist[1,2,3,4])

-- C
steps :: Int -> Cmd
steps 0 = Clist []
steps x = Clist [Call "vector" (Vlist [x-1, x-1, x-1, x]), Call "vector" (Vlist [x-1, x, x, x]), steps (x-1)]


-- ** Exercise 2. Digital Circuit Design Language **
-- a) Define the abstract syntax for the above language as a Haskell data type.
-- b) Represents the half adder circuit in abstract syntax, that is, as a Haskell 
--    data type value.
-- c) Define a Haskell function that implements a pretty printer for the abstract
--    syntax.

-- A
data Circuit = Cirs Gates Links | NoCir deriving Show
data Gates = Gat Number GateFn Gates | NoGates deriving Show
data GateFn = AND | OR | XOR | NOT deriving Show
data Links = From Number Number Number Number Links | NoLinks deriving Show

-- B
halfAddr :: Circuit 
halfAddr = Cirs (Gat 1 XOR (Gat 2 AND (NoGates))) (From 1 1 2 1 (From 1 2 2 2 (NoLinks)))

-- C
printGates :: Gates -> String
printGates NoGates = ""
printGates (Gat gn gfn remaining) = show gn ++ ": " ++ printGateFn gfn ++ " " ++ printGates remaining

printGateFn :: GateFn -> String
printGateFn AND = "AND"
printGateFn OR  = "OR"
printGateFn XOR = "XOR"
printGateFn NOT = "NOT"

printLinks :: Links -> String
printLinks NoLinks = ""
printLinks (From x1 x2 y1 y2 links) = "From: X: " ++ show x1 ++ " to " ++ show x2
                                     ++ " From: Y: " ++ show y1 ++ " to " ++ show y2
                                     ++ " " ++ printLinks links

printCir :: Circuit -> String
printCir NoCir = ""
printCir (Cirs gates links) = printGates gates ++ printLinks links

-- ** Exercise 3. Designing Abstract Syntax **
-- a) Represent the expression -(3+4)*7 in the alternative abstract syntax.
-- b) What are the advantages or disadvantages of either representation.
-- c) Define a function translate :: Expr -> Exp that translates expressions given 
--    in the first abstract syntax into equivalent expressions in the second syntax.

-- A
data Expr = N Int
          | Plus Expr Expr
          | Times Expr Expr
          | Neg Expr

data Op = Add | Multiply | Negate

data Exp = Num Int
         | Apply Op [Exp]

applyOps = Apply Multiply [Apply Negate [Apply Add [Num 3, Num 4]], Num 7]

-- B
-- Exp has a simpler syntax tree that allows for quicker parsing. However, the 
-- language can be cumbersome when representing complex arithmatic equations.

-- Meanwhile, Expr uses lists in its representation, so it is much easier to apply
-- operations to N numbers simultaneously. The downside is that parsing is more
-- difficult due to the presence of two data types.

-- C
translate :: Expr -> Exp
translate (N i) = Num i
translate (Plus e1 e2) = Apply Add (map translate [e1,e2])
translate (Times e1 e2) = Apply Multiply (map translate [e1,e2])
translate (Neg e1) = Apply Negate (map translate [e1])
