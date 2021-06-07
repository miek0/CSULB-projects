
import java.util.Scanner;

public class Lab4 {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please enter a positive integer: ");
		int n = sc.nextInt();
		int[] a = new int[n];
		int alen = a.length;
		int low = 0;
		
		generateArr(a);
		System.out.println("Generated a random array of size n.");
		display(a);
		
		System.out.println("Enter a number between 1 to n for the k least element: ");
		int key = sc.nextInt();
		
		int kth = quick_select(a,key,low,alen-1);
		System.out.println("The "+key+ "th least element in a is: "+kth);
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
		//checks for an empty array
		if(right == 0)
			return a[right];
		
		int index = partition(a,left,right);
		int leftlen = index - left + 1;
		if(leftlen == k)
			return a[index];
		else if(k<leftlen)
			return quick_select(a,k,left,index-1);
		else
			return quick_select(a,k-leftlen,index+1,right);
	}
	
	private static int partition(int a[],int left, int right) {
		int pivot =  a[right];
		int currentIndex = left-1;
		
		for(int i = left;i<right;i++) {
			if(a[i] <= pivot) {
				currentIndex++;
				int temp = a[currentIndex];
				a[currentIndex] = a[i];
				a[i] = temp;
			}
		}
		int newIndex = currentIndex+1;
		
		int temp = a[newIndex];
		a[newIndex] = a[right];
		a[right] = temp;
		
		return currentIndex+1;
	}

}
