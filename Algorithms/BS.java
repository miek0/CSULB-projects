import java.util.Scanner;

//Mike Zeng
//016392881
//CECS 328
//Lab 2
public class Lab2 {
	public static void main(String[] args) {
		System.out.println("Enter a positive integer: ");
		Scanner s = new Scanner(System.in);
		int n = s.nextInt();
		
		System.out.println("\nTesting Square root(ceiling answer):");
		System.out.println("Square root of "+n+" is:\n" + sqrt(n));
		
		System.out.println("\n\nDisplaying binary array: \n\n");
		System.out.println("Enter an array size of n: ");
		n = s.nextInt();
		int[] arr = binaryArr(n);
		display(arr);
		binarySearch(arr,1,0,arr.length-1);
		
		s.close();
	}
	
	public static int sqrt(int n) {
		//best cases
		if((n==0)||(n==1))
			return n;
		int i = 1;
		int end = n;
		int ans = 0;
		while(i <= end) {
			int mid = (i+end)/2;
			//if perfect square
			if(mid*mid == n)
				return mid;
			//finding other square roots, rounded to ceiling value
			if(mid <= n/mid) {
				i = mid + 1;
				ans = mid + 1; //+1 for rounding up to get ceiling value
			}else 
				end = mid - 1;
		}
		return ans;	
	}
	
	public static int[] binaryArr(int total) {
		int arr[] = new int[total];
		int k = (int)(Math.random()*total);
		for(int i = 0;i<k;i++) { //fills in 0s
			arr[i] = 0;
			for(int j = k;j<total;j++) //fills in 1s
				arr[j] = 1;
		}
		return arr;
	}
	
	public static void binarySearch(int[] a,int key,int start, int end) {
		int mid = (start+end)/2;
		int mid1 = mid + 1;
		//1 or 0 only array checking
		if(a[start] == 1) {
			System.out.println("All 0s");
			return;
		}
		if(a[end] == 0) {
			System.out.println("All 0s");
			return;
		}
		//finding the k in the binary array
		if(a[mid]==key) {
			if(a[mid-1] == 0)
				System.out.println("K is : "+mid);
			else
				binarySearch(a,key,start,mid-1);
		}else if(a[mid]==0) {
			if(a[mid1] == 1)
				System.out.println("K is : "+mid1);
			else
				binarySearch(a,key,mid1,end);
		}else
			System.out.println("not found");
		
	}
	
	public static void display(int[] a) {
		System.out.print("{ ");
		for(int i=0;i<a.length;i++)
			System.out.print(a[i]+" ");
		System.out.print("}\n");
	}
}
