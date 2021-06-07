import java.util.Arrays;
import java.util.Scanner;

//Mike Zeng
//016392881
//CECS 328
//Lab 1
public class Lab1 {
	public static void main(String[] args) {
		
		System.out.println("\n\n Testing Part A \n\n");
		/*Part A*/
		System.out.println("Part A: enter a positive integer:\n");
		Scanner s = new Scanner(System.in);
		int n = s.nextInt(); //user input. n = 10^5
				
		int[] a = new int[n]; //array a of n integers
		for(int j=0;j<a.length;j++) {//randomly assigns ints to elements in a
			a[j] = (int)(Math.random()*(2001) - 1000); //from -1000 to 1000
		}
		Arrays.sort(a); //sorted a in ascending order
		
		int avg = 100;
		double toSec = 1000000000.0;
		double elapsed1;
		double elapsed2;
		double totalTime = 0;
		
		for(int i=1;i<=avg;i++) {
			int keyA = (int)(Math.random()*(a.length));
			
			long startTime1 = System.nanoTime();
			linearSearch(a,keyA);
			long endTime1 = System.nanoTime();
			elapsed1 = ((endTime1 - startTime1)/1000000000.0);
			
			long startTime2 = System.nanoTime();
			binarySearch(a,keyA);
			long endTime2 = System.nanoTime();
			elapsed2 = ((endTime2 - startTime2)/1000000000.0);
			
			totalTime += (elapsed1 + elapsed2); 
		}
		double avgRT = totalTime/avg;
		System.out.println(avgRT + " is the average runtime in seconds. ");
		
		System.out.println("\n\n Testing Part B \n\n");
		
		/*Part B*/
		System.out.println("Part B: enter a new positive integer:\n");
		n = s.nextInt(); //user input. n = 10^5
				
		for(int j=0;j<a.length;j++) 		//randomly assigns ints to elements in a
			a[j] = (int)(Math.random()*(1000 + 1 + 1000) - 1000); //from -1000 to 1000
		Arrays.sort(a); //sorted a in ascending order
		
		int keyB = 5000; //worst-case
		double BSrunTime;
		double LSrunTime;

		System.out.println("Calculating worst case scenario of n=10^5 with key = 5000 (out of range for element values)");
		
		long startT = System.nanoTime();
		linearSearch(a,keyB);
		long endT = System.nanoTime();
		LSrunTime = (endT - startT)/toSec;
		System.out.println("Linear search worst case runtime is "+LSrunTime+" seconds.");
		
		startT = System.nanoTime();
		binarySearch(a,keyB);
		endT = System.nanoTime();
		BSrunTime = (endT - startT)/toSec;
		System.out.println("Binary search worst case runtime is "+BSrunTime+" seconds.\n\n");
		
		System.out.println("Estimation of LS and BS running time for worst_case scenario of n = 10^7\n\n");
		int NEWn = 10000000; //new worst case
		int[] NEWa = new int[NEWn];
		for(int k=0;k<NEWa.length;k++) 		//randomly assigns ints to elements in a
			NEWa[k] = (int)(Math.random()*(2001) - 1000); //from -1000 to 1000
		Arrays.sort(NEWa); //sorted a in ascending order
		int NEWkey = NEWa.length-1;;
		
		double worst_caseLS = 0;
		double worst_caseBS = 0;
		
		//testing worst case for linear search
		startT = System.nanoTime();
		linearSearch(NEWa,NEWkey);
		endT = System.nanoTime();
		worst_caseLS = (endT-startT)/toSec;
		System.out.println("Worst case running time for linear search(O(n)) is " + worst_caseLS);
		
		startT = System.nanoTime();
		//testing worst case for binary search
		binarySearch(NEWa,NEWkey);
		endT = System.nanoTime();
		worst_caseBS = (endT-startT)/toSec;
		System.out.println("Worst case running time for binary search(O(logn)) is " + worst_caseBS);
		
		System.out.println("\nCalculating runtime for 1 step in binary search.\n");
		double BStimeComplexity = 0; //O(logn) is the average running time for binary search
		startT = System.nanoTime();
		binarySearch(a,(int)(Math.random()*a.length));
		endT = System.nanoTime();
		BStimeComplexity = (endT-startT)/toSec;
		System.out.println("Running time for 1 binary search is " + BStimeComplexity+" seconds.");
		System.out.println("Average time to run 1 line of code is: "+instrPerSec(n,BSrunTime)+" seconds.");
	
		s.close();
	}
	 
	public static void linearSearch(int[] a, int key) {
		for(int i=0;i<a.length;i++) {
			if(a[i] == key) 
				System.out.println("The LS key was found at index "+i);
		}
	}
	
	public static void binarySearch(int[] a, int key) {
		int start = 0;
		int end = a.length-1;
		while(start <= end ) {
			int mid = (start + end)/2;
			//checks the middle between start and end at the beginning of each looping
			if(a[mid] == key) {
				System.out.println("The BS key was found at index " + mid);
			}
			if(a[mid] < key) 		//searches right section of array if key is greater than middle
				start = mid + 1;
			else // if(a[mid] > key)	//searches left section of array if key is less than middle
				end = mid - 1;
		}
	}
	
	public static double instrPerSec(int n, double avgRT) {
		//seconds per line
		double spl = 1/(Math.log(n)); //logn is the average time complexity of binary search
		return avgRT/spl;
	}
}