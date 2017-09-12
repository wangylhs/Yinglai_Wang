
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
public class Search extends Thread{
    int [][] x;// Array to be searched
    int num; // Number to be searched in x.
    int start;// Starting row number
    int end; // Starting column number
    boolean found; // Outcome of search (if num in x then true else false)
    
    public Search(int [][] x, int num, int start, int end){
        this.x=x;
        this.num=num;
        this.start=start;
        this.end=end;
    }// End of constructor
    
    
    // Main logic is here
    public void run(){
        int columns=x[0].length;// Number of columns in each row of x
        found=false; // Not yet found.
        // Set up loop. Note that start end end are
        // row nunmbers and not indices. Hence use start-1 and less
        // than end in the loops.
        for(int i=start-1; i<end; i++){
            for(int j=0; j<columns; j++){
                if(x[i][j]==num){
                    found=true;
                    break; // This terminates the inner loop.
                }
                if(found){
                    break; // This terminates the outer loop
                }
            }// End of inner loop
          
        }// End of outer loop
    }// End of run()
    
    
    // Get te outcome of search.
    public boolean getResult(){
        return found;
    }// End of getResult()
}// End of Search