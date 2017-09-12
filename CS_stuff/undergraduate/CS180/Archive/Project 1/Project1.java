import cs180.ConsoleInput;
import cs180.ConsoleOutput;
import java.util.Scanner;

class Project1
{
  static double array[];
  
  public static void input()
  {
    ConsoleInput userInput = new ConsoleInput(); 
    array = userInput.getScores();
  }
  
  public static void output(double[] numbers, int Start_Index, int End_Index, int group)
  {
    int size = End_Index - Start_Index + 1;
    
    double newArray[] = new double[size];
    ConsoleOutput cOutput = new ConsoleOutput();
    
    for(int i=0; i<newArray.length; i++, Start_Index++)
    {
      newArray[i] = numbers[Start_Index];
    }
    
     cOutput.printGroup(newArray, group);
  }
  
  public static void partition(int gnum)
  {
    double Max_Diff = 0;
    double Diff;
    int End_Index= 0;
    int Start_Index = 0;
     
       
    for(int j=0; j<gnum; j++)
    {          
      for(int i=Start_Index; i<array.length-1; i++)
      {
        Diff = array[i] - array[i+1];
      
        if(Diff > Max_Diff)
        {
          Max_Diff = Diff;
          End_Index = i;
        }
      }
      
      if(j==gnum-1)
      {
        End_Index = array.length-1;
      }
      
      output(array,Start_Index,End_Index,(j+1));
      Start_Index = End_Index + 1;
      Max_Diff = 0;
    }
  }
  
  public static void sort()
  {
    double Max=0;
    int Max_Index=0;
    double temp;
    int j;
    
    for(int i=0; i<array.length; i++)
    {
      for(j=i; j<array.length; j++)
      {
        if(Max < array[j])
        {
          Max = array[j];
          Max_Index = j;
        }
      }
      
        temp = array[i];
        array[i] = Max;
        array[Max_Index] = temp;
        Max = 0;
    }
    
    for(int i=0; i<array.length; i++)
    {
      System.out.println(array[i]);
    }
 }
    
  public static void main(String[] args)
  {
    int num;
    input();
    sort();
    System.out.println("Enter Number of Groups to be paritioned: ");
    
    Scanner in = new Scanner(System.in);
    num = in.nextInt();
    partition(num);
  }   
}