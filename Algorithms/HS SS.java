import java.util.Scanner;

public class Lab6 {
	
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please enter a positive integer: ");
		int n = sc.nextInt();			 //input for array size
		int[] a = new int[n]; 			//array a 
		int avg = 100;
		double toSec = 1000000000.0;
		
		System.out.println("Generating array of size "+n+": ");
		generateArr(a);
		display(a);
		
		long startT = System.nanoTime();
		heap_sort(a);
		long endT = System.nanoTime();
		System.out.println("Array after heap sort: ");
		display(a);
		System.out.println("Runtime of this array using heap_sort is: "+(endT-startT)/toSec+" seconds.\n");
		
		System.out.println("Taking average:");
		n = 1000;
		double hsTotal = 0.0;
		double ssTotal = 0.0;
		a = new int[n];
		
		for(int i=0;i<avg;i++) {
			generateArr(a);
			long startT2 = System.nanoTime();
			heap_sort(a);
			long endT2 = System.nanoTime();
			hsTotal += (endT2-startT2);
		}
		System.out.println("HS average runtime is: "+(hsTotal/avg)/toSec+ " seconds. ");
		
		for(int i=0;i<avg;i++) {
			generateArr(a);
			long startT3 = System.nanoTime();
			selection_sort(a);
			long endT3 = System.nanoTime();
			ssTotal += (endT3-startT3);
		}
		System.out.println("SS average runtime is: "+(ssTotal/avg)/toSec+ " seconds. ");
		
		sc.close();
	}
	
	/*creates an array of size n with random elements from -10000 to 10000*/
	public static void generateArr(int[] a) {
		for(int i=0;i<a.length;i++)
			a[i] = (int)(Math.random()*(20001)-10000);
	}
	
	/*displays the generated array*/
	public static void display(int[] a) {
		System.out.print("a = { ");
		for(int i=0;i<a.length;i++)
			System.out.print(a[i]+" ");
		System.out.print("}\n");
	}
	
	public static void build_MaxHeap(int[] a) {
		for(int i=(a.length/2)-1; i>= 0; i--)
			max_heapify(a, i , a.length);
	}
	
	public static void max_heapify(int[] a, int i, int n) {
		int largest = i;
		int left = 2*i + 1;
		int right = 2*i + 2;

		//if left is largest
		if (left < n && a[left] > a[largest])
			largest = left;
		//if right is largest
		if (right < n && a[right] > a[largest])
			largest = right;

		//if parent is not largest, swap and keep going
		if (largest != i) {
			swap(a, i, largest);
			max_heapify(a, largest, n);
		}
	}

	
	public static void heap_sort(int[] a) {
		build_MaxHeap(a);
		
		for(int i = a.length - 1;i >=0 ; i--) {
			swap(a, 0, i);
			max_heapify(a,0,i);
		}
	}

	public static void selection_sort(int[] a) {
		int alen = a.length;
		for(int i = 0;i<alen - 1; i++) {	//tracks smallest int left in array
			int min = i;
			for(int j=i;j<alen;j++) {		//iterates through the rest of array, looking for the newest smallest int
				if(a[j] < a[min])
					min = j;	
			}
			swap(a, i, min);
		}
	}
	
	private static void swap(int[]arr, int a , int b) {
		int temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;
	}
}