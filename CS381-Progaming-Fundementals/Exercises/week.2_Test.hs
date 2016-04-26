--
-- Test.hs  --  General purpose test routines
--

module Test (
  TestCase, mkCase, fromPair, (==>),
  TestSuite(..), mkSuite, testSuite, getCase,
  TestResult,
  Test,testWith,runTest,
  testiWith,testi
--   ,test2,test3
) where

data TestCase a b = TestCase String a b

instance (Show a,Show b) => Show (TestCase a b) where
  show (TestCase s x y) = "\nTEST CASE: "++descr s++
                          "\nFor argument: "++show x++
                          "\nExpected result: "++show y

mkCase :: (a' -> a) -> String -> a' -> b -> TestCase a b
mkCase f s x y = TestCase s (f x) y

fromPair :: (a,b) -> TestCase a b
fromPair (x,y) = TestCase "" x y

(==>) = curry fromPair


data TestSuite a b = TestSuite String [TestCase a b]

instance (Show a,Show b) => Show (TestSuite a b) where
  show (TestSuite s cs) = "\nTEST SUITE: "++s++"\n"++unlines (map show cs)
                           
mkSuite :: (a' -> a) -> String -> [(String,a',b)] -> TestSuite a b
mkSuite f s cs = TestSuite s (map (\(s,x,y)->TestCase s (f x) y) cs)

testSuite = TestSuite "A Test Suite"


getCase :: Int -> TestSuite a b -> TestCase a b
getCase n (TestSuite s cs) = TestCase (s++", "++s') x y 
                             where TestCase s' x y = cs!!(n-1)
  

data TestResult a b = OK String | Fail String [(String,a,b,b)]

instance (Show a,Show b) => Show (TestResult a b) where
  show (OK s)      = "TEST "++descr s++" PASSED!"
  show (Fail s cs) = "TEST "++descr s++" FAILED "++show (length cs)++" times because:"
                                             ++concatMap showC cs
descr "" = "<no description>"
descr s  = "\""++s++"\""
  
-- showC (s,x,r,y) = "\n\n"++if s=="" then "" else ("TEST: "++descr s++"\n")++
showC (s,x,r,y) = "\n\n"++ ("TEST: "++descr s++"\n")++
                  "For argument: "++show x++
                  "\nExpected result: "++show y++
                  "\nComputed result: "++show r


class Test t where
  testWith :: (b -> b -> Bool) -> (a -> b) -> t a b -> TestResult a b
  runTest     :: Eq b => (a -> b) -> t a b -> TestResult a b
  runTest = testWith (==)

instance Test TestCase where
  testWith eq f (TestCase s x y) | eq r y    = OK s
                                 | otherwise = Fail s [(s,x,r,y)]
                                 where r = f x
  
instance Test TestSuite where  
  testWith eq f (TestSuite s cs) = wrap $ foldr addFailures [] cs
            where addFailures (TestCase s x y) cs | eq r y    = cs
                                                  | otherwise = (s,x,r,y):cs
                                                  where r = f x
                  wrap [] = OK s
                  wrap l  = Fail s l

testiWith :: Int -> (b -> b -> Bool) -> (a -> b) -> TestSuite a b -> TestResult a b
testiWith i eq f t = testWith eq f (getCase i t)

testi :: Eq b => Int -> (a -> b) -> TestSuite a b -> TestResult a b
testi i = testiWith i (==)

-- test :: Eq b => (a -> b) -> TestCases a b -> TestResult a b
-- test = testWith (==)

-- test2 :: Eq c => (a -> b -> c) -> TestCases (a,b) c -> TestResult (a,b) c
-- test2 = test . uncurry
-- 
-- test3 :: Eq d => (a -> b -> c -> d) -> TestCases (a,b,c) d -> TestResult (a,b,c) d
-- test3 = test . uncurry3 where uncurry3 f = \(x,y,z)->f x y z


