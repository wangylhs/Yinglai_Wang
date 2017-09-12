
public class Quick3wayBM_V {
	static int frame = 0;
	
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
			insertion(a, lo, hi);
        	//StdDraw.setYscale(-(21)*(21-frame), (21)*frame + 10);
        	//draw(a, a[lo], lo, hi);
        	//frame++;
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
        for (int k = lo; k <= p; k++) swap(a, k, j--);
        for (int k = hi  ; k >= q; k--) swap(a, k, i++);
        if(med == 1){
            //Draw median-3.......................
        	StdDraw.setYscale(-(21)*(21-frame), (21)*frame + 10);
        	draw(a,v, lo, hi);
			frame++;
        }
        if(tukey == 1){
            //Draw tukey..........................
        	StdDraw.setYscale(-(21)*(21-frame), (21)*frame + 10);
        	draw(a,v, lo, hi);
			frame++;
        }
        
        if(j>lo){
        sort(a, lo, j);}
        if(i<hi){
        sort(a, i, hi);}
		}
	}
	public static void drawLayout(int a[]){
		int N = a.length;
		StdDraw.setCanvasSize(800, 1400);
		StdDraw.show(0);
		StdDraw.setXscale(-1, N+1);
		StdDraw.setPenRadius(.006);
		StdDraw.show(0);
	}
	public static void draw(int a[], int v, int lo, int hi){
		int size = a.length;
		for(int i=0; i<size; i++){
			if(i>lo && i<hi){
				if(a[i]==v){
					StdDraw.setPenColor(StdDraw.RED);
					StdDraw.line(i,0,i,a[i]/2);
					StdDraw.show(0);
				}else{
					StdDraw.setPenColor(StdDraw.BLACK);
					StdDraw.line(i,0,i,a[i]/2);
					StdDraw.show(0);
				}
			}else{
				StdDraw.setPenColor(StdDraw.GRAY);
				StdDraw.line(i,0,i,a[i]/2);
				StdDraw.show(0);
			}
		}
		
	}
	public static void drawL(int[] a){
		int size = a.length;
		for(int i=0; i<size; i++){
			StdDraw.setPenColor(StdDraw.BLACK);
			StdDraw.line(i,0,i,a[i]/2);
			StdDraw.show(0);
		}
				
	}
	
	public static void main(String[] args){
		//Read input
		int size = StdIn.readInt();
		int[] numbers = new int[size];
		for(int i=0; i<size; i++){
			numbers[i] = StdIn.readInt();
		}
        //Initialize the canvas
		drawLayout(numbers);
        //draw the original array
    	StdDraw.setYscale(-(21)*(21-frame), (21)*frame + 10);
		drawL(numbers);
		frame++;
		sort(numbers);
        //draw the final array
    	StdDraw.setYscale(-(21)*(21-frame), (21)*frame + 10);
    	drawL(numbers);
		}
}