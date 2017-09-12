


public class Quick3wayBMwang {
	public static void sort(int[] a){
		sort(a, 0, a.length-1);
	}

	private static void swap(int[] a, int i, int j){
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	private static void insertion(int[] a, int lo, int hi){
		for(int i = lo; i <= hi; i++){
			for(int j = lo; j < i; j++){
				if(a[i]<a[j])
					swap(a, i, j);
			}
		}
	}
	private static int getMedian(int[] a, int i, int j, int k){
		int median=i;
		if(a[i]>=a[j]&&a[i]>=a[k]){
			if(a[j]>=a[k]){median=j;}
			else{median=k;}
		}
		else if(a[j]>=a[i]&&a[j]>=a[k]){
			if(a[i]>=a[k]){median=i;}
			else{median=k;}
		}
		else if(a[k]>=a[j]&&a[k]>=a[i]){
			if(a[j]>=a[i]){median=j;}
			else{median=i;}
		}
		return median;
	}

	
	private static void sort(int[] a, int lo, int hi){
		int med = 0;
		int tukey = 0;
		int subsize = hi - lo + 1;

		
		if(subsize <= 8){
			StdOut.println("(Insertion_Sort, " + lo+", " + hi+")");
			insertion(a, lo, hi);
			return;
		}
		else{
		if(subsize <= 40){
			med = 1;
			int median = getMedian(a, lo, lo+subsize/2, hi );
			swap(a, median, lo);
		}else {
			tukey = 1;
			int OneEighth = subsize/8;
            int mid = lo + subsize/2;
            int m1 = getMedian(a, lo, lo + OneEighth, lo + OneEighth+ OneEighth);
            int m2 = getMedian(a, mid - OneEighth, mid, mid + OneEighth);
            int m3 = getMedian(a, hi - OneEighth-OneEighth, hi - OneEighth, hi); 
            int nintherMed = getMedian(a, m1, m2, m3);
            swap(a, nintherMed, lo);
            
		}
		int i = lo+1, j = hi;
		int p = lo, q = hi + 1;
		int v = a[lo];
        while (true) {
           
            while (a[i] < v)
                i++;if (i == hi) break;
            while (v < a[j])
                j--;if (j == lo) break;
            if (i >= j) break;
            swap(a, i, j);
            if (a[i] == v) swap(a, ++p, i);
            if (a[j] == v) swap(a, --q, j);
            i++;j--;
        }
       
        if(i==j){swap(a,++p,i);i++;}

        if(med == 1)
        	StdOut.println("(median_of_3, " +lo+", "+v+", "+p+", "+i+", "+j+", "+q+", "+hi+")");
        if(tukey == 1)
        	StdOut.println("(Tukey_Ninether, " +lo+", "+v+", "+p+", "+i+", "+j+", "+q+", "+hi+")");
        
        
        
        for (int k = lo; k <= p; k++) swap(a, k, j--);
        for (int k = hi  ; k >= q; k--) swap(a, k, i++);
        if(j>lo){
        sort(a, lo, j);}
        if(i<hi){
        sort(a, i, hi);}
		}
	}
	
	public static void main(String[] args){
		//Read input
		int size = StdIn.readInt();
		int[] numbers = new int[size];
		for(int i=0; i<size; i++){
			numbers[i] = StdIn.readInt();
		}
		sort(numbers);
		
		
	}
}
