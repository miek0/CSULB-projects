import java.util.Scanner;
//import java.util.Arrays;

public class Lab3 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please enter a positive integer: ");//n=1000
		int n = sc.nextInt();
		int[] a = new int[n];
		
		int alen = a.length;
		int avgT = 100;
		double toSec = 1000000000.0;
		
		double QStotal = 0;
		double IStotal = 0;
		
//		int[]b = {4,-90,88,30,5,-11,100,9,69};
//		System.out.println(Arrays.toString(b));
//		quick_sort(b,0,(b.length-1));
//		System.out.println(Arrays.toString(b));
		
		for(int r = 0; r < avgT; r++) {
			for(int i=0;i<alen;i++)
				a[i] = (int)(Math.random()*(10001)-5000);
			
			/*quick sorting a*/
			long QSstart = System.nanoTime();
			quick_sort(a,0,(alen-1));
			long QSend = System.nanoTime();
			QStotal += (double)((QSend-QSstart)/toSec);
			
		}
		
		
		for(int r = 0; r < avgT; r++) {
			for(int i=0;i<alen;i++)
				a[i] = (int)(Math.random()*(10001)-5000);
			
			/*insertion sorting a*/
			long ISstart = System.nanoTime();
			insertion_sort(a);
			long ISend = System.nanoTime();
			IStotal += (double)((ISend-ISstart)/toSec);
			
		}
		
		double avgQS = QStotal/avgT;
		double avgIS = IStotal/avgT;
		
		System.out.println("The average-running time of quick_sort is: "+avgQS+ " seconds. \nThe average-running time of insertion_sort is: "+avgIS+" seconds.");
		
		/*testing instructions ran per second for insertion*/
		System.out.println("Number of instructions ran per second in insertion sort is "+ isInstrPerSec(n,avgIS) +" instructions/sec.");
		sc.close();
	}

	public static void quick_sort(int[] n, int low, int high) {
		if(low < high) {
			int pivot = partition(n, low, high);
			quick_sort(n, low, pivot-1);
			quick_sort(n, pivot+1, high);
		}
	}
	
	private static int partition(int a[],int left, int right) {
		int temp = medianOf3(a, left, right);
		swap(a,temp,right);
		int pivot =  a[right];
		int currentIndex = left-1;
		
		for(int i = left;i<right;i++) {
			if(a[i] <= pivot) {
				currentIndex++;
				swap(a, currentIndex, i);
			}
		}
		int newPivot = currentIndex+1;

		swap(a, newPivot, right);
		
		return newPivot;
	}
	
	private static int medianOf3(int[]arr, int left, int right) {
		int mid = (left+right)/2;
		if (arr[right] < arr[left]) 
			swap(arr,left,right);
		if (arr[mid] < arr[left]) 
			swap(arr,left,mid);
		if (arr[right] < arr[mid]) 
			swap(arr,left,right);
		return mid;
	}
	
	private static void swap(int[]arr, int a , int b) {
		int temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;
	}
	
	public static void insertion_sort(int[] n) {
		for(int i = 1;i<n.length;i++) {
			int temp = n[i];
			int j = i;
			while(j > 0 && n[j-1] > temp) {
				n[j] = n[j-1];
				j--;
			}
			n[j] = temp;
		}
	}
	
	public static double isInstrPerSec(int n, double avgRT) {return avgRT/(double)(n*n);}
}
