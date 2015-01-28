module Num where

import Prelude hiding (succ, pred)
  


----------------------------------------------------------------------
-- Natural numbers
----------------------------------------------------------------------

-- data Dig  = Zero | One | Two | Three
-- data Natx = D Dig | Comp Dig Natx
-- 
data Nat = Zero | Succ Nat
           deriving (Eq,Show)
--            deriving Eq


-- (1) values
-- 
one   = Succ Zero
two   = Succ one
three = Succ two
nine  = mult three three


-- (2) simple functions and predicates
-- 
succ :: Nat -> Nat
succ = Succ
-- OR:
-- succ Zero     = Succ Zero
-- succ (Succ n) = Succ (Succ n)
-- OR:
-- succ n = Succ n

pred :: Nat -> Nat
pred Zero     = Zero
pred (Succ n) = n

-- the type Bool is predefined in Haskell:
-- 
-- data Bool = True | False
-- 

isZero :: Nat -> Bool
isZero Zero = True
isZero _    = False
-- OR:
-- isZero n = if n==Zero then True else False
-- OR:
-- isZero n = n==Zero
-- OR:
-- isZero = (==Zero)

add :: Nat -> Nat -> Nat
add Zero     m = m
add (Succ n) m = Succ (add n m)

{-

add two Zero =
add (Succ one) Zero =
add (Succ (Succ Zero)) Zero =
Succ (add (Succ Zero) Zero) =
Succ (Succ (add Zero Zero)) =
Succ (Succ (Zero))

-}

-- (3) create customized show function
-- to deal conveniently with larger numbers
-- 
nat2int :: Nat -> Int
nat2int Zero     = 0
nat2int (Succ n) = 1+nat2int n

-- instance Show Nat where
--   show n = show (nat2int n)



-- (4) more functions and predicates
-- 
equal :: Nat -> Nat -> Bool
equal Zero     Zero     = True
equal (Succ n) (Succ m) = equal n m
-- -- equal (Succ n) (Succ m) = if equal n m then True else False
equal _        _        = False



gt :: Nat -> Nat -> Bool
gt (Succ n) Zero     = True
gt (Succ n) (Succ m) = gt n m
gt _        _        = False

-- multiply two natural numbers
-- 
mult :: Nat -> Nat -> Nat
mult Zero     _ = Zero
mult (Succ n) m = add m (mult n m)



----------------------------------------------------------------------
-- Binary numbers
----------------------------------------------------------------------

data Digit = O | I
             deriving (Eq,Show)

data Bin = Single Digit 
         | Comp   Digit Bin

instance Show Bin where
  show (Single d) = show d
  show (Comp d b) = show d ++ show b

b4 = Comp I (Comp O (Single O))
b5 = suc b4
b6 = suc b5
b7 = suc b6
b8 = suc b7

-- sucC computes the successor of a binary number
-- plus a carry bit/digit, represented as a pair
-- 
sucC :: Bin -> (Digit,Bin)
sucC (Single O) = (O,Single I)
sucC (Single I) = (I,Single O)
sucC (Comp O b) = (O,Comp c b')
                  where (c,b') = sucC b
sucC (Comp I b) = case sucC b of
                    (O,b') -> (O,Comp I b')
                    (I,b') -> (I,Comp O b') 

-- suc computes the successor of a binary number
-- 
suc :: Bin -> Bin
suc b = case sucC b of
          (O,b') -> b'
          (I,b') -> Comp I b'
          
-- mulTwo multiplies a binary number by 2
-- 
mulTwo :: Bin -> Bin
mulTwo (Single d) = Comp d (Single O)
mulTwo (Comp d b) = Comp d (mulTwo b)

{-
To avoid multiple leading zeros, one could expand
these first definition into two cases:

       mulTwo (Single O) = Single O
       mulTwo (Single I) = Comp I (Single O)
       
However, there's nothing in the definition of Bin that prevents 
the user from using the constructor "Comp O b".  How would I 
change the definition of Bin so that "Comp O b" evaluates to "b"?

You can't (at least not in the data type definition).
If you want to prevent certain representations, you
could use what is called "smart constructors".

-}

bin :: [Digit] -> Bin
bin [d]    = Single d
bin (O:ds) = bin ds
bin ds     = comp ds
             where comp [d]    = Single d
                   comp (d:ds) = Comp d (comp ds)


-- divTwo divides a binary number by 2
--
divTwo :: Bin -> Bin 
divTwo (Comp d (Single _)) = Single d
divTwo (Comp d b)          = Comp d (divTwo b)
divTwo (Single _)          = Single O


-- The data type Bin is basically a type for non-empty lists.
-- Therefore, we can implement all the functions on binary functions
-- also using the following representation, which is based on the 
-- built-in list type.
-- 
type BinL = [Digit]

l4 = [I,O,O]
l7 = [I,I,I]

-- sucR computes the successor of a binary number represented
-- by a list in reverse, that is, the list [O,O,I] represents
-- 4 and not 1. That allows us to start with the last digit
-- at the front of the list and progress the successor computation
-- down the list.
--
sucR :: BinL -> BinL
sucR (O:ds) = I:ds
sucR (I:ds) = O:sucR ds
sucR []     = [I]

-- sucL is computing the successor for the list representation
-- of a binary number. It can be conveniently defined using 
-- sucR and reverse.
-- 
sucL :: BinL -> BinL
sucL = reverse . sucR . reverse
-- sucL ds = reverse (sucR (reverse ds))

-- mulTwo multiplies a binary number by 2
--  
mulTwoL :: BinL -> BinL
mulTwoL ds = ds ++ [O]

-- divTwo divides a binary number by 2
--  
divTwoL :: BinL -> BinL
divTwoL = init


-- convert digits and binary numbers to Nat
-- 
dig2nat :: Digit -> Nat
dig2nat O = Zero
dig2nat I = Succ Zero

-- bin2natR works, like sucR, on the reverse list
-- representation
-- 
bin2natR :: BinL -> Nat
bin2natR [d]    = dig2nat d
bin2natR (d:ds) = add (dig2nat d) (mult two (bin2nat ds))

-- bin2nat can be conveniently defined using bin2natR and reverse.
-- 
bin2nat :: BinL -> Nat
bin2nat = bin2natR . reverse


nat2bin :: Nat -> BinL
nat2bin Zero     = [O]
nat2bin (Succ n) = sucL (nat2bin n)


