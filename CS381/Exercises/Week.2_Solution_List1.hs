module List1 where


data List = Empty | Cons Int List
            deriving Show


l = Cons 1 (Cons 2 (Cons 3 Empty))



-- rest removes the first element from a list.
rest :: List -> List 
rest Empty       = Empty
rest (Cons _ xs) = xs


-- member determines whether an integer is an element of a list.
member :: Int -> List -> Bool 
member _ Empty      = False
-- member i (Cons x xs) = if i==x then True else member i xs
-- member i (Cons x xs) = i==x || member i xs
member i (Cons x xs) | i==x      = True
                     | otherwise = member i xs


-- snoc adds an integer to the end of a list.
snoc :: Int -> List -> List
snoc i Empty       = Cons i Empty
snoc i (Cons x xs) = Cons x (snoc i xs)


-- rev reverses the elements in a list.
rev :: List -> List
rev Empty       = Empty
rev (Cons x xs) = snoc x (rev xs) 



--
-- Here are the definitions of the list functions for the built-in
-- list representation.
--
-- Note that [a] means a list of arbitrary type.
--
-- Note also that [1,2] is an abbreviation for 1:2:[]
--

l' = [1,2,3]


rest' :: [a] -> [a]
rest' []     = []
rest' (_:xs) = xs


-- The "Eq a =>" in the type means that the definition works only for 
-- lists whose element type supports the equality function. This restriction
-- is needed since "==" is used in the definition of member'.
member' :: Eq a => a -> [a] -> Bool 
member' _ []     = False
member' i (x:xs) | i==x      = True
                 | otherwise = member' i xs


snoc' :: a -> [a] -> [a]
snoc' i []     = [i]  -- note that [i] is the same as i:[]
snoc' i (x:xs) = x:snoc' i xs  


rev' :: [a] -> [a]
rev' []     = []
rev' (x:xs) = snoc' x (rev' xs)

