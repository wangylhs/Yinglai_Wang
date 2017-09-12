/*	Name:	Yinglai Wang
 *  Login:	wang1105
 */

public class Rhyming{
	static String[] list = new String[100];
	static String[] reversedList;
	static String[] suffix = new String[100];
	static int size = 0;
	static int maxWlength = 0;

	public static String[] Resize(String a[], int size){
		String[] array = new String[size];
		if(size > a.length){
			for(int i=0; i < a.length; i++)
				array[i] = a[i];
		}else if(size < a.length){
			for(int i=0; i < size; i++)
				array[i] = a[i];
		}
		return array;
	}
	public static void InsertionSort(String[] array, int length){
		String temp;
		for(int i=0; i<length; i++){
			for(int j=i; j>0; j--){
				if(array[j-1].compareTo(array[j]) > 0){
					temp = array[j];
					array[j] = array[j-1];
					array[j-1] = temp;
				}
			}
		}
	}
	public static String[] reverseList(String[] array, int length){
		String[] s = new String[length];
		for(int i=0; i<length; i++){
			s[i] = reverse(array[i]);
		}
		return s;
	}
	public static String reverse(String a){
		String s = "";
		for(int i=a.length()-1; i>=0; i--){
			s += a.charAt(i);
		}
		return s;
	}

	public static void getSuffix(String[] array, int size, int wordlength){
		int sl;
		int count;
		String[] s = new String[size];
		String suf;
		//wordlength is the maximum word's length in this list
		//the following loop will check every word's suffix depends on the length of suffix
		for(sl=1; sl < wordlength; sl++){
			count = 0;
			for(int i=0; i<size; i++){
				if(array[i].length() >= sl){
					//add the symbol "|" between prefix and suffix of the word
					s[count] = array[i].substring(0,sl) + "|" + array[i].substring(sl, array[i].length());
					s[count] = reverse(s[count]);
					count++;
				}
			}
			//use quicksort sort the list
			quicksort(s, 0, count-1);
			int newCount = 0;
			//delete the set that only have one word in it
			for(int i=0; i<count; i++){
				
				String [] b = s[i].split("\\|");
				if (i>0 && s[i-1].split("\\|")[1].compareTo(b[1])==0) {
					s[newCount++] = s[i];
				} else if (i<count-1 && s[i+1].split("\\|")[1].compareTo(b[1])==0) {
					s[newCount++] = s[i];
				}
			}
			count = newCount;
			//Format Output
			for(int i=0; i<count; i++){
				String[] b;
				String a;
				b = s[i].split("\\|");
				//Check if there is any inappropriate words in every sorted array
				if(i==0 || s[i-1].split("\\|")[1].compareTo(b[1])!=0){
					int j, t;
					for(j=i; j<count; j++) {
						String [] m = s[i].split("\\|");
						String [] n = s[j].split("\\|");
						if (!m[1].equals(n[1])) break;
					}
					j--;
					for(t=i; t<j; t++) {
						String [] m = s[t].split("\\|");
						String [] n = s[t+1].split("\\|");
						if (m[0].length()==0 || n[0].length()==0 ||
								m[0].charAt(m[0].length()-1) != n[0].charAt(n[0].length()-1)) break;
					}
					if (t<j)
						StdOut.print("[ " + s[i]);
					else
						i = j;
				}
				else if(i == count-1 || b[1].compareTo(s[i+1].split("\\|")[1]) != 0)
					StdOut.print(", " + s[i] + " ]\n");
				else
					StdOut.print(", " + s[i]);

			}

		}
	}
	//compare words
	//first depends on the suffix, use String.compareTo, if commen, sort to alphabetical order
	//because we are using the sorted reversed list, which means it is already sorted by length of suffix
	//second depends on the alphabetical order of the whole word, not only prefix part
	public static int partition(String [] a, int left, int right, int pivotIndex)
	{	
		String pivot = a[pivotIndex];
		do
		{
			while (suffixCmp(a[left] , pivot) < 0) left++;
			while (suffixCmp(a[right] , pivot) > 0 ) right--;
			if (left < right && suffixCmp(a[left], a[right]) != 0)
			{
				String t = a[left];
				a[left] = a[right];
				a[right] = t;
			}
			else
			{
				return right;
			}
		} while (left < right);

		return right;
	}
	public static void quicksort(String[] s, int left, int right)
	{
		if (left<right) {
			int pivot = (left + right) / 2; 
			int pivotNew = partition(s, left, right, pivot);
			quicksort(s, left, pivotNew - 1);
			quicksort(s, pivotNew + 1, right);
		}

	}
	//function of compare two suffixes
	public static int suffixCmp(String a, String b) {
		String [] s1 = a.split("\\|");
		String [] s2 = b.split("\\|");

		int r = s1[1].compareTo(s2[1]);
		if (r==0) {
			return a.replaceAll("\\|", "").compareTo(b.replaceAll("\\|", ""));
		} else
			return r;
	}
	
	public static void main(String[] args){
		//read and save the original input into "list" using dynamicl sized array
		for(int i=0; !StdIn.isEmpty(); i++){
			if(list[list.length-1] != null)
				list = Resize(list, list.length*2);
			if(list[list.length/4] == null)
				list = Resize(list, list.length/2);
			list[i] = StdIn.readString();
			if(list[i].length() > maxWlength)
				maxWlength = list[i].length();
			size++;
		}
		//reverse every word of the list
		reversedList = reverseList(list, size);
		//use insertion sort sort the reversed list
		InsertionSort(reversedList, size);
		//executing every requirment of this project
		getSuffix(reversedList, size, maxWlength);
	}
}