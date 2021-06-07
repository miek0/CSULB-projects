/*
 * Mike Zeng
 * CECS 424-05
 * Assignment 3
 */
using System;
using System.Collections.Generic;
using System.Linq;

namespace _424hw3sharp
{
    class Assignment3
    {
        //display functions
        static void display_num(List<double> d){
            for (int i = 0; i < d.Count; i++)
                Console.Write(d[i]+" ");
        }

        static void display_people(Dictionary<string, int> p){
            foreach (KeyValuePair<string, int> person in p)
                Console.Write(person.Key + ","+ person.Value + " ");
        }

        static void Main(string[] args)
        {
            //data structures
            List<double> numbers = new List<double> { 645.32, 37.40, 76.30, 5.40, -34.23, 1.11, -34.94, 23.37, 635.46, -876.22, 467.73, 62.26 };
            Dictionary<string, int> people = new Dictionary<string, int>() { { "Hal", 20 }, {"Susann", 31}, {"Dwight", 19},
                                                                             {"Kassandra" , 21 }, {"Lawrence", 25 }, {"Cindy" , 22},
                                                                             {"Cory" , 27 }, {"Mac" , 19 }, {"Romana" , 27},
                                                                             {"Doretha" , 32 }, { "Danna" , 20}, {"Zara" , 23},
                                                                             {"Rosalyn" , 26 }, { "Risa" , 24}, { "Benny" , 28},
                                                                             { "Juan" , 33 }, {"Natalie" , 25 } };
            //display and order list of numbers
            Console.WriteLine("List of numbers:");
            display_num(numbers);
            Console.WriteLine("\nOrdered numbers:");
            var ordered_num = numbers.OrderBy(x => x).ToList();     //ordered numbers in ascending fashion
            display_num(ordered_num);
            //display and order list of people by name then age
            Console.WriteLine("List of people:");
            display_people(people);
            Console.WriteLine("\nOrdered people by name (alphabetically):");
            var alpha_ordered_people = people.OrderBy(p => p.Key).ToDictionary(p => p.Key, p => p.Value);   //ordered people alphabetically
            display_people(alpha_ordered_people);
            Console.WriteLine("\nOrdered people by descending age (then alphabetically):");
            var desc_age_ordered_people = alpha_ordered_people.OrderByDescending(p => p.Value).ToDictionary(p => p.Key, p => p.Value);  //ordered people descending by age then alphabetically
            display_people(desc_age_ordered_people);
            Console.WriteLine();
        }
    }
}
