import java.util.Scanner;

public class Lab7 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please enter a positive integer: ");
		int n = sc.nextInt();			 //input for array size
		double[] a = new double[n]; 			//array a 
		double toSec = 1000000000.0;	//for converting to seconds
		
		/*generates and displays array*/
		generateArr(a);
		display(a);
		
		sc.close();
	}
	
	public static int MPSS(int[] a,int low, int high) {
		int mid = (low+high)/2;
		
		if(low == high)
			return a[low];
		else {
			int left = MPSS(a,low,mid);
			int right = MPSS(a,mid+1,high);
			int all = arrMaxSum(a,low,mid,high);
			if((left > right) && (left > all))
				return left;
			if((right > left) && (right > all))
				return right;
			else
				return all;
		}
	}
	
	private static int arrMaxSum(int a[], int low, int mid, int high) {
		int temp = 0;
		int left_max = 0;
		int right_max = 0;
		
		for(int i = mid; i >= low; i--) {
			temp += a[i];
			if(temp > left_max)
				left_max = temp;
		}
		
		temp = 0;
		
		for(int i = mid+1; i <= high; i++) {
			temp += a[i];
			if(temp > right_max)
				right_max = temp;
		}
		
		return left_max+right_max;
	}
	
	public static void quick_sort(double[] n, int low, int high) {
		if(low < high) {
			int pivot = partition(n, low, high);
			quick_sort(n, low, pivot-1);
			quick_sort(n, pivot+1, high);
		}
	}
	
	private static int partition(double a[],int left,int right) {
		int temp = medianOf3(a, left, right);
		swap(a,temp,right);
		double pivot =  a[right];
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
	
	private static int medianOf3(double[]arr, int left, int right) {
		int mid = (left+right)/2;
		if (arr[right] < arr[left]) 
			swap(arr,left,right);
		if (arr[mid] < arr[left]) 
			swap(arr,left,mid);
		if (arr[right] < arr[mid]) 
			swap(arr,left,right);
		return mid;
	}
	
	private static void swap(double[]arr, int a , int b) {
		double temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;
	}

	/*creates an array of size n with random elements from -100 to 100*/
	public static void generateArr(double[] a) {
		for(int i=0;i<a.length;i++)
			a[i] = Math.round((Math.random()*(41.0)-20.0)*10.0)/10.0;
	}
	
	/*displays the generated array*/
	public static void display(double[] a) {
		int alen = a.length;
		System.out.println("Generated array of size "+alen);
		System.out.print("a = { ");
		for(int i=0;i<alen;i++)
			System.out.print(a[i]+" ");
		System.out.print("}\n\n");
	}
}
