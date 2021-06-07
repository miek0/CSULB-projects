package part1;

import java.io.File;

import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;
import java.util.TreeMap;

public class Part1 {

	public static void main(String[] args) throws IOException {
		// Variables to record times
		Long insTime = 0L, searchTime = 0L;

		// User input scanner
		Scanner userIn = new Scanner(System.in);

		// Creating file for QnotfollowedByU and Scanner
		File listFile = new File("QnotfollowedbyU.txt");
		Scanner tmFileScanner = new Scanner(listFile);
		// Creating file for scrabbleValues and Scanner
		File scrabbleFile = new File("scrabbleValues.txt");
		Scanner scrabbleScanner = new Scanner(scrabbleFile);

		// Display Menu
		System.out.println("========================== MENU ==========================");
		System.out.println("(H) Use HashMaps	(T) Use TreeMap		(Q) Quit");
		System.out.println("==========================================================");

		// Ask user for input
		System.out.print("Please enter a selection: ");
		// Set selection to user input, whatever is put in will work in this case, no
		// exception thrown
		char selection = userIn.next().toString().toLowerCase().charAt(0);
		// Closer user input scanner
		userIn.close();

		switch (selection) {
		case 'h': // Use HashMaps
			// Create HashMaps and scanner for listFile
			HashMap<Integer, String> hm = new HashMap<Integer, String>();
			HashMap<Character, Integer> hmLetterValues = new HashMap<Character, Integer>();
			Scanner hmFileScanner = new Scanner(listFile);

			// Run through the file and add the words to the HashMap
			int i = 0;
			// Start timer
			insTime = System.nanoTime();
			while (hmFileScanner.hasNextLine()) {
				// add to HashMap (i, word on the line);
				hm.put(i, hmFileScanner.nextLine());
				i++;
			}
			// Stop the timer
			insTime = System.nanoTime() - insTime;

			// Run through the scrabble values file and insert them into a HashMap
			while (scrabbleScanner.hasNextLine()) {
				// Get the line from the file and assign it to temp
				String temp = scrabbleScanner.nextLine();
				// hm.put(the actual character, the numerical value)
				hmLetterValues.put(temp.charAt(0), Integer.parseInt(temp.substring(2, temp.length())));
			}

			// Start search timer
			searchTime = System.nanoTime();
			// Iterate through the values in the HashMap
			for (Object value : hm.values()) {
				int score = 0;
				// score = score + (value of current character)
				for (int j = 0; j < value.toString().length(); j++) {
					score += hmLetterValues.get(value.toString().toLowerCase().charAt(j));
				}
				// Display the score for the word
				System.out.println(value.toString() + " has a score of " + score);
			}
			// Stop search timer
			searchTime = System.nanoTime() - searchTime;

			// Display results and close scanners
			System.out.println("Insertion time into the HashMap: " + insTime + "ns");
			System.out.println("Time spent searching the HashMap for values: " + searchTime + "ns");
			hmFileScanner.close();
			scrabbleScanner.close();
			break;
		case 't': // Use TreeMaps
			TreeMap<Integer, String> tm = new TreeMap<Integer, String>();
			TreeMap<Character, Integer> tmLetterValues = new TreeMap<Character, Integer>();
			Scanner scrabbleScanner2 = new Scanner(scrabbleFile);

			// i is used as key value for insert
			i = 0;
			// start timer
			insTime = System.nanoTime();
			while (tmFileScanner.hasNextLine()) {
				// insert each line (word) of the file
				tm.put(i, tmFileScanner.nextLine());
				i++;
			}
			// stop timer
			insTime = System.nanoTime() - insTime;

			i = 0;
			while (scrabbleScanner2.hasNextLine()) {
				// Get the line from the file and assign it to temp
				String temp = scrabbleScanner2.nextLine();
				// put(the letter, the value of the letter) into TreeMap
				tmLetterValues.put(temp.charAt(0), Integer.parseInt(temp.substring(2, temp.length())));
				i++;
			}

			// start search timer
			searchTime = System.nanoTime();
			// Iterate through each word in the TreeMap
			for (Object value : tm.values()) {
				int score = 0;
				for (int j = 0; j < value.toString().length(); j++) {
					// score = score + value of current letter from the TreeMap
					score += tmLetterValues.get(value.toString().toLowerCase().charAt(j));
				}
				// Display score of each word
				System.out.println(value.toString() + " has score of " + score);
			}
			// Stop Search Timer
			searchTime = System.nanoTime() - searchTime;

			// Display Results
			System.out.println("Insertion time into the TreeMap: " + insTime + "ns");
			System.out.println("Time spent searching the TreeMap for values: " + searchTime + "ns");

			// Close Scanners
			tmFileScanner.close();
			scrabbleScanner.close();
			break;
		case 'q':
			// Exit program
			System.exit(0);

		default:
			System.out.println("Invalid selection");
			break;
		}
	}

}
