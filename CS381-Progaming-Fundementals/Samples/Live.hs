module Live where

--------------------------------------------------------------------------------
-- Lambda (anonymous) functions

-- One way of implementing "double" is to define the "times2" function, and then
-- map that function across the list.
times2 :: Int -> Int
times2 x = 2 * x

double :: [Int] -> [Int]
double xs = map times2 xs

-- However, coming up with definitions and names can sometimes clutter your
-- file, or be otherwise inconvenient.  Instead, we can use a lambda function
-- (sometimes called an anonymous function).  Here we use a lambda function
-- which has an identical implementation to "times2" from above, but doesn't
-- require the extra work.
doubleLambda :: [Int] -> [Int]
doubleLambda xs = map (\x -> 2 * x) xs


--------------------------------------------------------------------------------
-- Point free style

-- This function is _NOT_ written in point free style.  This is because we bind
-- the name "xs" to the [Int] parameter.
mySumRegular :: [Int] -> Int
mySumRegular xs = foldr (+) 0 xs

-- Sometimes it is cleaner to drop that parameter.  In this case we can simply
-- look and think "okay, you're folding the "+" function with a default
-- parameter of 0.  People who have seen a lot of Haskell will often think
-- this is intuitive, and that adding the extra "xs" name is just clutter.
-- In general, this is a matter of taste.  It's often best to err on the side of
-- naming your parameters
--
-- If you want to play around with it, consider installing the Haskell package
-- "pointfree", which will convert expressions into this style (often with
-- terrifying results).
mySumPF :: [Int] -> Int
mySumPF = foldr (+) 0


--------------------------------------------------------------------------------
-- Type classes

-- Type classes are a way of restricting a polymorphic type variable.  If we
-- have a function whose type declaration is "a -> a", then we call "a" a type
-- variable, and it is totally unrestricted.  That is, our function can accept
-- absolutely any type as input.
--
-- Sometimes, however, we want to accept parameters with lots of different
-- types, but not quite everything.  For example, consider this function which
-- only works on integers.

timesTwoInt :: Int -> Int
timesTwoInt x = 2 * x

-- It works okay so long as we are content with only ever being able to use
-- integers, but what about natural numbers, floats, doubles, and so on?  We
-- can't make our function "a -> a" because there are some things it doesn't
-- make sense to multiply.  What would you do if somebody passed in a list,
-- for instance?
--
-- Instead, we can use a type that says "we can take any type, so long as it
-- is a numeric type.  Numeric types know how to respond to multiplication.
--
-- In Haskell this is usually the "Num" type class, but don't worry about
-- memorizing or defining any of them for the time being.  This is just to
-- demonstrate one way of writing a more general function.

timesTwoNum :: Num a => a -> a
timesTwoNum x = 2 * x

-- Sometimes it can be enlightening to see what Haskell things the type of
-- certain functions is.  Once you've written a function, try commenting out the
-- type declaration, reloading the file, and then asking GHCi what it infers the
-- type to be, using the :t command.
--
-- For instance, if we type ":t timesTwoNum" with the type signature removed
-- (or ":t \x -> 2 * x") we indeed get "Num a => a -> a"


--------------------------------------------------------------------------------
-- Partial function application / Currying

timesThenPlus :: Int -> Int -> Int -> Int
timesThenPlus x t p = (x * t) + p

times2ThenPlus :: Int -> Int -> Int
times2ThenPlus = timesThenPlus 2

times2and5ThenPlus :: Int -> Int
times2and5ThenPlus = times2ThenPlus 5


--------------------------------------------------------------------------------
-- Data type pattern matching

data Nat = Zero
         | Suc Nat
         deriving (Show)

two :: Nat
two = Suc (Suc Zero)

plus2 :: Nat -> Nat
plus2 (Zero) = Suc (Suc Zero)
plus2 (Suc n) = Suc (Suc (Suc n))

four :: Nat
four = plus2 two

-- This is named Zero' (with the apostraphe) to avoid a name clash with the
-- natural number definition.
data Bin = One | Zero'
         deriving (Show)

-- This is an incomplete definition.  How many cases do you need?  Four?  Are
-- you sure?
xor :: Bin -> Bin -> Bin
xor (One) (One) = Zero'
xor (One) (Zero') = One
xor _ _ = undefined
