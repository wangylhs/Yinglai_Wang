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
	
	static class Node{
		Node prev = null;
		Node next = null;
		int data;
		public Node(int data){
			this.data = data;
		}
		public void appendToTail(int data){
			Node end = new Node(data);
			Node n = this;
			while(n.next!=null){
				n = n.next;
			}
			end.prev = n;
			n.next = end;
			
		}
		public void appendToHead(int data){
			Node head = new Node(data);
			Node n = this;
			while(n.prev!=null){
				n = n.prev;
			}
			n.prev = head;
			head.next = n;
		}
	}
	
	public static void printList(Node n){
		Node p = n;
		while(p.prev!=null){
			p = p.prev;
		}
		while(p.next!=null){
			System.out.println(p.data);
			p = p.next;
		}
		System.out.println(p.data);
	}
	
	static Node deleteNode(Node head, int d){
		Node p = head;
		if(p.data == d){
			p.next.prev = null;
			return p.next;
		}
		while(p.next!=null){
			if(p.next.data == d){
				if(p.next.next!=null){
					p.next = p.next.next;
					p.next.prev = p;
					return head;
				}else{
					p.next = null;
					return head;
				}
			}
			p = p.next;
		}
		return head;
	}
	
	//remove duplicates
	public static void removeDup(Node head){
		
	}
	
	public static void main(String[] args){
		/*String s1 = "abdjskl";
		String s2 = "ajskabd";
		System.out.println(checkPerm(s1,s2));
		String s = "abcde";
		System.out.println(StringCompr(s));
		
		int[] array = {-40,-20,-1,1,2,3,5,7,9,12,13};
		System.out.println(magicFast(array));
		*/
		StringMani.Node list = new StringMani.Node(0);
		list.appendToTail(1);
		//list.appendToHead(-1);
		list.appendToTail(2);
		list.appendToTail(3);
		printList(list);
		list = deleteNode(list,2);
		System.out.println();
		printList(list);
	}
}
