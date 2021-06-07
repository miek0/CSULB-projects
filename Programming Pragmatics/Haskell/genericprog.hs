-- Mike Zeng
-- CECS 424
-- Assignment 3
module Main where

-- I imported sorting and ordering functions from the Haskell Data library:
-- sort is used to sort the numbers since it's only 1 data type
-- sort is also used to sort the pairs of data via fst (alphabetically by name) or snd (order of age)
-- sortBy was used for descending sort by age but keeps alphabetical order intact 
-- Haskell's polymorphism allows these functions to be called on any data type 
import Data.List
import Data.Ord

numbers = [645.32, 37.40, 76.30, 5.40, -34.23, 1.11, -34.94, 23.37, 635.46, -876.22, 467.73, 62.26]
people = [("Hal", 20), ("Susann", 31), ("Dwight", 19), ("Kassandra", 21), ("Lawrence", 25), ("Cindy", 22), ("Cory", 27),("Mac", 19), ("Romana", 27), ("Doretha", 32), ("Danna", 20), ("Zara", 23), ("Rosalyn", 26), ("Risa", 24), ("Benny",28), ("Juan", 33), ("Natalie", 25)]

main = do
-- display list of numbers and ordered list of numbers
 putStrLn("Numbers list: ")
 print(numbers)
 putStrLn("Ordered numbers: ")
 print(sort(numbers))
-- display list of people and orders people first by name then by age
 putStrLn("\nList of people: ")
 print(people)
 putStrLn("\nOrder people by name (alphabetically): ")
 let alphaSort = sort(people)
 print(alphaSort)
 putStrLn("\nOrder people by age (descending, then alphabetically): ")
 let descSort = sortBy (comparing (Down . snd))
 print(descSort(alphaSort))