public class Quick3wayBM_Vbzhan{
	private boolean Median,Turkey;
	private static final int CUTOFF=8;
	private static final int StdLen=40;
	private static int frame=0;
	private static Comparable val;

	public static void visualInit(Comparable[] source){
		StdDraw.setCanvasSize(800, 600);
		StdDraw.show(0);
		StdDraw.setXscale(-1, source.length+1);
		StdDraw.setPenRadius(.006);
		StdDraw.show(0);
	}
	private void drawing(Comparable[] source, int lo, int hi, Comparable val){
		StdDraw.setYscale(-(21)*(21-frame), (21)*frame + 10);
		for(int i=0; i<source.length; i++){
			int l = (Integer)source[i];
			if(i>lo && i<hi && source[i]==val){
				StdDraw.setPenColor(StdDraw.RED);
				StdDraw.line(i, 0, i, l);
				StdDraw.show(0);
			}
			else if(i>lo && i<hi){
				StdDraw.setPenColor(StdDraw.BLACK);
				StdDraw.line(i, 0, i, l);
				StdDraw.show(0);
			}
			else{
				StdDraw.setPenColor(StdDraw.GRAY);
				StdDraw.line(i, 0, i, l);
				StdDraw.show(0);
			}
		}
		frame++;

	}

	public void sort(Comparable[]source){
		int lo=0;
		int hi=source.length-1;
		//draw original array
		StdDraw.setYscale(-(21)*(21-frame), (21)*frame + 10);
		for(int i=0; i<source.length; i++){
			int l = (Integer)source[i];
			StdDraw.setPenColor(StdDraw.BLACK);
			StdDraw.line(i, 0, i, l);
			StdDraw.show(0);
		}
		frame++;
		sort(source,lo,hi);
	}

	private void sort(Comparable[]source,int lo,int hi){

		Median=false;
		Turkey=false;
		int i,j,p,q;
		int median=0;
		int length=hi-lo+1;
		if(length<=CUTOFF){      //insertion
			InsertionSort(source,lo,hi);
			drawing(source, lo, hi, val);
		}
		else{ 
			if(length<=StdLen){  //median of 3
				Median=true;
				median=findMedian(source,lo,length/2+lo,hi);
				swap(source,lo,median);
			}
			else{                  //Turkey ninther
				Turkey=true;
				median=TurkeyNither(source,lo,hi);
				swap(source,lo,median);
			}
			val=source[lo];           //3-way
			p=lo;
			i=lo+1;
			q=hi+1;
			j=hi;
			while(true){

				while (source[i].compareTo(val)<0||source[j].compareTo(val)>0){
					if(source[i].compareTo(val)<0){i++;}
					if(source[j].compareTo(val)>0){j--;}
				}

				if(i>=j){break;}

				swap(source,i,j);
				if (source[i].compareTo(val)==0){ p++;swap(source, p, i);}   
				if (source[j].compareTo(val)==0){ q--;swap(source, q, j);}
				i++;j--;
			}
			if(j==i){p++;swap(source,p,i);i++;}
			int Q=(q==hi+1? hi:q);



			for(int z=lo;z<=p;z++){
				swap(source,z,j);
				j--;}
			for(int z=hi;z>=q;z--){
				swap(source,z,i);
				i++;}
			///
			drawing(source, lo, hi, val);

			if(lo<j){
				sort(source,lo,j);}
			if(i<hi){
				sort(source,i,hi);}
		}

	}

	private void InsertionSort(Comparable[]source,int lo,int hi){
		if(hi-lo>0){
			for(int i=lo+1;i<=hi;i++){
				int j=lo;
				for(j=lo;j<i;j++){
					if(source[i].compareTo(source[j])<=0){break;}
				}
				if(j<i){
					Comparable temp=source[i];
					int z=0;
					for(z=i;z>j;z--){
						source[z]=source[z-1];
					}
					source[z]=temp;
				}
			}
		}
	}

	private int findMedian(Comparable[]source,int lo,int mid,int hi){
		int median=0;
		if(source[lo].compareTo(source[hi])>=0&&source[lo].compareTo(source[mid])>=0){
			median=source[mid].compareTo(source[hi])<=0? hi : mid;
		}
		else if(source[mid].compareTo(source[hi])>=0&&source[mid].compareTo(source[lo])>=0){
			median=source[lo].compareTo(source[hi])<=0? hi : lo;
		}
		else if(source[hi].compareTo(source[lo])>=0&&source[hi].compareTo(source[mid])>=0){
			median=source[mid].compareTo(source[lo])<=0? lo : mid;
		}
		return median;
	}

	private int TurkeyNither(Comparable[]source,int lo,int hi)
	{
		int a=(hi-lo+1)/8;
		int A,B,C;
		A=findMedian(source,lo,lo+a,lo+a+a);
		B=findMedian(source,(hi-lo+1)/2+lo-a,(hi-lo+1)/2+lo,(hi-lo+1)/2+lo+a);
		C=findMedian(source,hi-a-a,hi-a,hi);
		return findMedian(source,A,B,C);
	}


	private void swap(Comparable[]source,int a,int b){
		Comparable temp=source[a];
		source[a]=source[b];
		source[b]=temp;
	}


	public static void main(String[]args){
		Quick3wayBM_Vbzhan qs=new Quick3wayBM_Vbzhan();
		int count=0;
		int num;
		int size=StdIn.readInt();
		Comparable [] Num=new Comparable[size];
		while(count<size){
			num=StdIn.readInt();
			Num[count]=num;
			count++;
		}
		visualInit(Num);
		qs.sort(Num);
		//draw final
		StdDraw.setYscale(-(21)*(21-frame), (21)*frame + 10);
		for(int i=0; i<Num.length; i++){
			int l = (Integer)Num[i];
			StdDraw.setPenColor(StdDraw.BLACK);
			StdDraw.line(i, 0, i, l);
			StdDraw.show(0);
		}
		frame++;

	}
}