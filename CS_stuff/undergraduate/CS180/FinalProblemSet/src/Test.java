
public class Test {
	public static void main(String[] args){
		int[] array = {3,4,8,90,12,0,2,3};
		Sum2 sEven = new Sum2(array, "even");
		Sum2 sOdd = new Sum2(array,"odd");
		
		sEven.start();
		sOdd.start();
		try{
			sEven.join();
			sOdd.join();
		}catch(Exception e){}
		System.out.println(sEven.getSum());
		System.out.println(sOdd.getSum());
	}
}
