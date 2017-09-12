/*
 * 
 * CS 180 Fall 2011
 * Final Exam Solutions
 * 
 * Author: Aditya Mathur
 * December 19, 2011
 * 
 * Q2
 */
public class Test{
    // A method to populate the array in
    // which the search is to take place. This
    // method was not required of the students.
    
    public static int [][] createArray(int n){
        int [][] a=new int[n][n];
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                a[i][j]=i+j;
              //  System.out.print (a[i][j]+" "); // For debugging
            }
           // System.out.println (); // For debugging
        }
        return a;
    }// End of createArray()
    
    public static void main(String [] arg){
        int n=10;// Size of the 2-D array.
        int [][] x=new int[n][n]; // Create an nxn array
        int num=18; // An arbitrary number to be searched 
        x=createArray(n); // Add elements to x 
        // Create threads.
        Search s1=new Search(x, num, 1, n/2);
        Search s2=new Search(x, num, n/2+1, n);
        // Start threads
        s1.start();
        s2.start();
        
        // Wait for the threads to complete.
        try{
            s1.join();
            s2.join();
        }catch(Exception e){}
        
        // Get the outcome of seach from each thread.
        boolean f1=s1.getResult();
        boolean f2=s2.getResult();
        
        if(f1 || f2){
            System.out.println(num+" found");
        }else{
            System.out.println(num+" not found");
        }
    }// End of main()
}// End of Test