import java.util.Scanner;

public class Lab4 {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please enter a positive integer for array size to test: ");
		int n = sc.nextInt();
		int[] a = new int[n];
		int alen = a.length;
		int low = 0;
		generateArr(a);
		display(a);
		
		System.out.println("Enter a number between 1 to n for the k least element: ");
		int key = sc.nextInt();
		int kth = quick_select(a,key,low,alen-1);
		System.out.println("The kth least element in a is: "+kth);
		
		System.out.println("\nGenerating a new array for B)");
		
		int[] b = new int[n];
		generateArr(b);
		display(b);
		
		System.out.println("Enter a number between 1 to n for the max k elements: ");
		key = sc.nextInt();
		int[] max = maxKnums(b,0,a.length-1,key);
		System.out.println("The max "+key+" elements are: ");
		display(max);
		
		sc.close();
	}
	
	public static void generateArr(int[] a) {
		for(int i=0;i<a.length;i++)
			a[i] = (int)(Math.random()*(201)-100);
	}
	
	public static void display(int[] a) {
		System.out.print("{ ");
		for(int i=0;i<a.length;i++)
			System.out.print(a[i]+" ");
		System.out.print("}\n");
	}
	
	public static int quick_select(int[] a, int k, int left,int right) {
		if(left==right)
			return a[left];
		int index = partition(a,left,right);
		int length = index - left + 1;
		if(length == k)
			return a[index];
		else if(k<length)
			return quick_select(a,k,left,index-1);
		else
			return quick_select(a,k-length,index+1,right);
	}
	
	public static int[] maxKnums(int[] a,int left, int right, int k) {
		int[] max = new int[k];
		int pivot = partition(a,left,right);
		int maxK = a.length - k;

		if(pivot == maxK) {
			for(int i=0;i<k;i++)
				max[i] = a[maxK+i];
			return max;
		}else if(pivot < maxK)
			return maxKnums(a,pivot+1,right,k);
		else
			return maxKnums(a, left,pivot-1,k);
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
		int newIndex = currentIndex+1;

		swap(a, newIndex, right);
		
		return currentIndex+1;
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
}