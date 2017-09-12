
public class Problem2 {
	static int[] a = {1,2,3,4,5,6,7,8,9};
	
	
	public static void main(String[] args){
		System.out.println(bSearch(a,9));
	}
	
	public static boolean bSearch(int[] a, int x){
		int mid = a.length/2;
		
		if(a.length==0){
			return false;
		}
		if(a.length==1){
			if(a[0]==x){
				return true;
			}else{
				return false;
			}
		}else if(x==a[mid]){
			return true;
		}else if(x>a[mid]){
			int[] temp = new int[mid+1];
			for(int i=0; i<mid+1; i++){
				temp[i] = a[mid+i];
			}
			return bSearch(temp,x);
		}else if(x<a[mid]){
			int[] temp = new int[mid];
			for(int i=0; i<mid; i++){
				temp[i] = a[i];
			}
			return bSearch(temp,x);
		}
		return false;
	}
}
