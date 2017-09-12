
public class ArrayTest {
	public static void exchange(int[] a, int[] b){
		int[] temp;
		temp = a;
		System.out.println(a[0]+" "+b[0]);
		a=b;
		System.out.println(a[0]+" "+b[0]);
		b=temp;
		System.out.println(a[0]+" "+b[0]);
	}
	public static void main(String[] args){
		int[] x={1,2,3}, y={4,5,6};
		exchange(x,y);
		System.out.println(x[0]+" "+y[0]);
	}
}
