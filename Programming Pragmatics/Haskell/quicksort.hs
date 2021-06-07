module Main where --module name

arr = [4,65,2,-31,0,99,2,83,782,1] --declare list of unsorted integers

--quick sort
qsort :: (Ord a) => [a] -> [a] --constrains qsort to type a
qsort [] = []  
qsort (x:xs) =   
 let smallerSorted = qsort [a | a <- xs, a <= x]  
     biggerSorted = qsort [a | a <- xs, a > x]  
 in  smallerSorted ++ [x] ++ biggerSorted  

--merge sort
halve :: [a] -> ([a],[a])
halve xs = (take lhx xs, drop lhx xs)
           where lhx = length xs `div` 2

msort :: Ord a => [a] -> [a]
msort []  = []
msort [x] = [x]
msort  xs = merge (msort left) (msort right)
            where (left,right) = halve xs

merge :: Ord a => [a] -> [a] -> [a] -- merge two sorted lists to a sorted list
merge [] ys = ys                    -- if one
merge xs [] = xs                    --   or the other list is empty merging is trivial
merge (x:xs) (y:ys)                 -- merge two non-empty lists
  | x <= y    = x : merge xs (y:ys) -- if the left element is smaller then output it first
  | otherwise = y : merge (x:xs) ys --   otherwise output the right element first
  
main = do
 print(arr)