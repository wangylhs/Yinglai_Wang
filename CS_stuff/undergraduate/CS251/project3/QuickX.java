public class QuickX {
    private static final int CUTOFF = 8;  // cutoff to insertion sort, must be >= 1

    public static void sort(Comparable[] a) {
        sort(a, 0, a.length - 1);
    }

    private static void sort(Comparable[] a, int lo, int hi) { 
        int N = hi - lo + 1;
        int med = 0;
        int tukey = 0;
        // cutoff to insertion sort
        if (N <= CUTOFF) {
			StdOut.println("(Insertion_Sort, " + lo+", " + hi+")");
            insertionSort(a, lo, hi);
            return;
        }

        // use median-of-3 as partitioning element
        else if (N <= 40) {
        	med = 1;
            int m = median3(a, lo, lo + N/2, hi);
            exch(a, m, lo);
        }

        // use Tukey ninther as partitioning element
        else  {
        	tukey = 1;
            int eps = N/8;
            int mid = lo + N/2;
            int m1 = median3(a, lo, lo + eps, lo + eps + eps);
            int m2 = median3(a, mid - eps, mid, mid + eps);
            int m3 = median3(a, hi - eps - eps, hi - eps, hi); 
            int ninther = median3(a, m1, m2, m3);
            exch(a, ninther, lo);
        }

        // Bentley-McIlroy 3-way partitioning
        int i = lo, j = hi+1;
        int p = lo, q = hi+1;
        while (true) {
            Comparable v = a[lo];
            while (less(a[++i], v))
                if (i == hi) break;
            while (less(v, a[--j]))
                if (j == lo) break;
            if (i >= j) break;
            exch(a, i, j);
            if (eq(a[i], v)) exch(a, ++p, i);
            if (eq(a[j], v)) exch(a, --q, j);
        }
        
        if(med == 1)
        	StdOut.println("(median_of_3, " +lo+", "+a[lo]+", "+p+", "+i+", "+j+", "+q+", "+hi+")");
        if(tukey == 1)
        	StdOut.println("(Tukey_Ninether, " +lo+", "+a[lo]+", "+p+", "+i+", "+j+", "+q+", "+hi+")");
        exch(a, lo, j);
        i = j + 1;
        j = j - 1;
        for (int k = lo+1; k <= p; k++) exch(a, k, j--);
        for (int k = hi  ; k >= q; k--) exch(a, k, i++);

        sort(a, lo, j);
        sort(a, i, hi);
    }


    // sort from a[lo] to a[hi] using insertion sort
    private static void insertionSort(Comparable[] a, int lo, int hi) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(a[j], a[j-1]); j--)
                exch(a, j, j-1);
    }


    // return the index of the median element among a[i], a[j], and a[k]
    private static int median3(Comparable[] a, int i, int j, int k) {
        return (less(a[i], a[j]) ?
               (less(a[j], a[k]) ? j : less(a[i], a[k]) ? k : i) :
               (less(a[k], a[j]) ? j : less(a[k], a[i]) ? k : i));
    }

   /***********************************************************************
    *  Helper sorting functions
    ***********************************************************************/
    
    // is v < w ?
    private static boolean less(Comparable v, Comparable w) {
        return (v.compareTo(w) < 0);
    }

    // does v == w ?
    private static boolean eq(Comparable v, Comparable w) {
        return (v.compareTo(w) == 0);
    }
        
    // exchange a[i] and a[j]
    private static void exch(Object[] a, int i, int j) {
        Object swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }



    // test client
    public static void main(String[] args) {
    	int size = StdIn.readInt();
    	Integer[] a = new Integer[size];
    	for(int i=0; i<size; i++)
    		a[i] = StdIn.readInt();
    	sort(a);
    	

    }

}
