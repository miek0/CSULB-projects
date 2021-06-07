package part2;

import java.io.File;
import java.io.IOException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.TreeSet;

public class Part2 {
	final private static File ALICE = new File("alice30.txt");

	public static void main(String[] args) {

		System.out.println("=================== MENU ===================");
		System.out.println("     (T)ree Set	            (H)ash Set");
		System.out.println("============================================");
		Scanner userIn = new Scanner(System.in);
		System.out.print("Please make a selection: ");

		switch (userIn.next().toString().toLowerCase().charAt(0)) {
		case 't':
			try {
				treeMethod();
			} catch (IOException e) {
				e.printStackTrace();
			}
			break;
		case 'h':
			try {
				hashMethod();
			} catch (IOException e) {
				e.printStackTrace();
			}
			break;
		default:
			System.out.println("Invalid Selection");

		}
		userIn.close();
	}

	public static void hashMethod() throws IOException {
		Scanner aliceScan = new Scanner(ALICE);
		HashSet<String> hs = new HashSet<String>();
		long timer = 0;

		try {
			timer = System.nanoTime();
			while (aliceScan.hasNext()) {
				hs.add(aliceScan.next());
			}
			timer = System.nanoTime() - timer;
		} catch (Exception e) {
			e.printStackTrace();
		}

		System.out.println("The HashSet insert took " + timer + "ns");

		timer = System.nanoTime();
		for (int i = 0; i < 100; i++) {
			hs.contains("the");
		}
		timer = System.nanoTime() - timer;

		System.out.println("The HashSet search took " + timer + "ns");
		aliceScan.close();
	}

	public static void treeMethod() throws IOException {
		Scanner aliceScan = new Scanner(ALICE);
		TreeSet<String> ts = new TreeSet<String>();
		long timer = 0;

		try {
			timer = System.nanoTime();
			while (aliceScan.hasNext()) {
				ts.add(aliceScan.next());
			}
			timer = System.nanoTime() - timer;
		} catch (Exception e) {
			e.printStackTrace();
		}

		System.out.println("The TreeSet insert took " + timer + "ns");

		timer = System.nanoTime();
		for (int i = 0; i < 100; i++) {
			ts.contains("the");
		}
		timer = System.nanoTime() - timer;

		System.out.println("The TreeSet search took " + timer + "ns");
		aliceScan.close();

	}

}
