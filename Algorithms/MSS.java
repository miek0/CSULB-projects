import java.util.Scanner;

public class Lab5 {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please enter a positive integer: ");
		int n = sc.nextInt();			 //input for array size
		int[] a = new int[n]; 			//array a 
		double toSec = 1000000000.0;	//for converting to seconds
		
		/*generates and displays array*/
		generateArr(a);
		display(a);
		
		/*runs the MSS functions
		 * first tests the best_case MSS of time complexity of O(n) and tracks the run time
		 * second test the average_case MSS of time complexity of O(nlogn) and tracks the run time
		 */
		long startBC = System.nanoTime();
		int mss1 = mssBC(a);
		long endBC = System.nanoTime();
		double best_case = (endBC-startBC)/toSec;
		
		long startAC = System.nanoTime();
		int mss2 = mssAC(a,0,a.length-1);
		long endAC = System.nanoTime();
		double avg_case = (endAC-startAC)/toSec;
		
		System.out.println("MSS of array a on time complexity O(n) is : "+mss1+" with run time of "+best_case+" seconds. \nMSS of array a on time complexity O(nlogn) is : "+mss2+" with run time of "+avg_case+" seconds.");
		
		sc.close();
	}
	
	public static int mssBC(int[] a) {
		int temp = 0;					//temp value to count total added
		int max = a[0];					//current maximum sum
		for(int i=0;i<a.length;i++) {
			temp += a[i];				
			if(temp > max) 				//if temp is greater than current max, set current max to temp
				max = temp;
			if(temp < 0)
				temp = 0;
		}
		return max;
	}
	
	/* find MSS through recursion */
	public static int mssAC(int[] a,int low, int high) {
		int mid = (low+high)/2;
		
		if(low == high)										//base case
			return a[low];
		else {
			int left_sum = mssAC(a,low,mid);				//find the max of left of array
			int right_sum = mssAC(a,mid+1,high);			//find the max of right of array
			int all_sum = arrMaxSum(a,low,mid,high); 		//find the max of the entire array
			
			int maxOfLeftRight = Math.max(left_sum,right_sum);
			return Math.max(maxOfLeftRight, all_sum);
		}
	}
	
	/* same logic as the mssBC
	 * used to find the max sum of entire array */
	private static int arrMaxSum(int a[], int low, int mid, int high) {
		int temp = 0;
		int left_max = 0;
		int right_max = 0;
		
		for(int i = mid;i >= low; i--) {
			temp += a[i];				
			if(temp > left_max) 
				left_max = temp;
		}
		
		temp = 0;
		for(int i = mid+1;i <= high; i++) {
			temp += a[i];				
			if(temp > right_max)
				right_max = temp;
		}
		
		return left_max + right_max;
	}
	
	/*creates an array of size n with random elements from -100 to 100*/
	public static void generateArr(int[] a) {
		for(int i=0;i<a.length;i++)
			a[i] = (int)(Math.random()*(201)-100);
	}
	
	/*displays the generated array*/
	public static void display(int[] a) {
		System.out.println("Generated array of size n");
		System.out.print("a = { ");
		for(int i=0;i<a.length;i++)
			System.out.print(a[i]+" ");
		System.out.print("}\n\n");
	}
}

