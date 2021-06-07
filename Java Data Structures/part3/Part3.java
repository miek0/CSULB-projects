package Part3;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.InputMismatchException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

public class Part3 {

	public static void main(String[] args) throws IOException {
		File shList = new File("shList.txt");

		System.out.println("============== MENU ==============");
		System.out.println(" 1.) Array List	  2.) Linked List ");
		System.out.println("==================================");

		System.out.print("Make a selection: ");
		switch (getInt()) {
		case 1:
			alMethod(shList);
			break;
		case 2:
			llMethod(shList);
			break;
		default:
			System.out.println("Invalid input");
		}
	}

	public static void alMethod(File f) {
		ArrayList<String> al = new ArrayList<String>();
		long timer = 0;
		int teams;

		try {
			Scanner scan = new Scanner(f);
			while (scan.hasNextLine()) {
				al.add(scan.nextLine());
			}
			scan.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		ListIterator<String> it = al.listIterator();
		timer = System.nanoTime();
		while (it.hasNext()) {
			it.next();
		}

		while (it.hasPrevious()) {
			it.previous();
		}
		timer = System.nanoTime() - timer;
		System.out.println("The iterating time for ArrayList is " + timer + "ns");

		System.out.print("How many teams are playing? ");
		teams = getInt();

		ArrayList<ArrayList<String>> theTeams = new ArrayList<ArrayList<String>>();
		for (int i = 0; i < teams; i++) {
			try {
				ArrayList<String> temp = new ArrayList<String>();
				Iterator<String> iter = al.iterator();
				while (iter.hasNext()) {
					temp.add(iter.next().toString());
				}
				Collections.shuffle(al);
				theTeams.add(temp);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		int ele;
		System.out.print("What position in the list is to be used for retrieving and inserting elements? ");
		while (true) {
			ele = getInt()-1;
			if (ele - 1 < 100 && ele-1 > -1) {
				break;
			} else {
				System.out.println("The number must be between 1 and 100");
			}
		}

		timer = System.nanoTime();
		for (int i = 0; i < theTeams.size(); i++) {
			System.out.println("Team " + (i + 1) + ": " + theTeams.get(i).get(ele));
		}
		timer = System.nanoTime() - timer;
		System.out.println("Total time for retrieval in an Array List was: " + timer + "ns");
		timer = System.nanoTime();
		for (int i = 0; i < theTeams.size(); i++) {
			theTeams.get(i).set(ele, "Potato");
		}
		timer = System.nanoTime() - timer;
		System.out.println("Total time for replacement in an Array List was: " + timer + "ns");

		int random = (int) Math.random() * (101);
		timer = System.nanoTime();
		for (int i = 0; i < theTeams.size(); i++) {
			theTeams.get(i).get(random);
		}
		timer = System.nanoTime() - timer;
		System.out.println("Total time for retrieval of random element in an Array List was: " + timer + "ns");

	}

	public static void llMethod(File f) {

		LinkedList<String> ll = new LinkedList<String>();
		long timer = 0;
		int teams;

		try {
			Scanner scan = new Scanner(f);
			while (scan.hasNextLine()) {
				ll.add(scan.nextLine());
			}
			scan.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		ListIterator<String> it = ll.listIterator();
		timer = System.nanoTime();
		while (it.hasNext()) {
			it.next();
		}

		while (it.hasPrevious()) {
			it.previous();
		}
		timer = System.nanoTime() - timer;
		System.out.println("The iterating time for Linked List is " + timer + "ns");

		while (true) {
			try {
				System.out.print("How many teams are playing? ");
				teams = getInt();
				break;
			} catch (InputMismatchException e) {
				System.out.println("Invalid input, please try again.");
			}
		}

		LinkedList<LinkedList<String>> theTeams = new LinkedList<LinkedList<String>>();
		for (int i = 0; i < teams; i++) {
			try {
				LinkedList<String> temp = new LinkedList<String>();
				Iterator<String> iter = ll.iterator();
				while (iter.hasNext()) {
					temp.add(iter.next().toString());
				}
				Collections.shuffle(ll);
				theTeams.add(temp);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		System.out.print("What position in the list is to be used for retrieving and inserting elements? ");
		int ele;
		while (true) {
			ele = getInt()-1;
			if (ele - 1 < 100 && ele-1 > -1) {
				break;
			} else {
				System.out.println("The number must be between 1 and 100");
			}
		}

		timer = System.nanoTime();
		for (int i = 0; i < theTeams.size(); i++) {
			System.out.println("Team " + (i + 1) + ": " + theTeams.get(i).get(ele));
		}
		timer = System.nanoTime() - timer;
		System.out.println("Total time for retrieval in a Linked List was: " + timer + "ns");
		timer = System.nanoTime();
		for (int i = 0; i < theTeams.size(); i++) {
			theTeams.get(i).set(ele, "Potato");
		}
		timer = System.nanoTime() - timer;
		System.out.println("Total time for replacement in a Linked List was: " + timer + "ns");

		int random = (int) Math.random() * (101);
		timer = System.nanoTime();
		for (int i = 0; i < theTeams.size(); i++) {
			theTeams.get(i).get(random);
		}
		timer = System.nanoTime() - timer;
		System.out.println("Total time for retrieval in a Linked List of random element was: " + timer + "ns");

	}

	public static int getInt() {
		int out;
		while (true) {
			Scanner input = new Scanner(System.in);
			try {
				out = input.nextInt();
				break;
			} catch (InputMismatchException e) {
				System.out.println("Invalid input, please try again.");
			}input.close();
		}
		return out;
	}

}
