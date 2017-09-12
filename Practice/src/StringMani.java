import java.util.Arrays;


public class StringMani {
	
	//determine if a string has all unique characters
	public static boolean isUnique(String s){
		if(s.length()>128){
			return false;
		}
		boolean[] b = new boolean[128];
		for(int i=0;i<s.length();i++){
			if(b[s.charAt(i)]!=false){
				return false;
			}
			b[s.charAt(i)] = true;
		}
		return true;
		
	}
	
	//check if one is permutation of other
	public static boolean checkPerm(String s1, String s2){
		if(s1.length()!=s2.length()) return false;
		char[] c1 = s1.toCharArray();
		char[] c2 = s2.toCharArray();
		Arrays.sort(c1);
		Arrays.sort(c2);
		for(int i=0; i<c1.length;i++){
			if(c1[i]!=c2[i]) return false;
		}
		return true;
	}
	//String compress
	public static String StringCompr(String s){
		StringBuilder sb = new StringBuilder();
		int ct = 1;
		int last = 0;
		sb.append(s.charAt(0));
		for(int i=1;i<s.length();i++){
			last = sb.length()-1;
			if(s.charAt(i)==sb.charAt(last)){
				ct++;
			}else{
				sb.append(ct);
				ct=1;
				sb.append(s.charAt(i));
			}
		}
		sb.append(ct);
		if(sb.length()<s.length()){
			return sb.toString();
		}else{
			return s;
		}
	}
	//magic index
	public static int magicFast(int[] array){
		return magicFast(array, 0, array.length-1);
	}
	public static int magicFast(int[] array, int start, int end){
		if(end<start){
			return -1;
		}
		int mid = (start+end)/2;
		if(array[mid]==mid){
			return mid;
		}else if(array[mid]<mid){
			return magicFast(array,mid+1,end);
		}else if(array[mid]>mid){
			return magicFast(array,start,mid-1);
		}
		return -1;
	}
	
	
	public static void main(String[] args){
		/*String s1 = "abdjskl";
		String s2 = "ajskabd";
		System.out.println(checkPerm(s1,s2));
		String s = "abcde";
		System.out.println(StringCompr(s));
		*/
		int[] array = {-40,-20,-1,1,2,3,5,7,9,12,13};
		System.out.println(magicFast(array));
	}
}
