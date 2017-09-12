/* What is the output of the following program? */

public class Child {

  public boolean equals( Child other ) {
    System.out.println( "Inside of Child.equals" );
    return false;
  }

  public static void main( String [] args ) {
    Object t1 = new Child();
    Child t2 = new Child();
    Child t3 = new Child();
    Object o1 = new Object();

    int count = 0;
    System.out.println( count++ );// prints 0
    t1.equals( t2 ) ;
    System.out.println( count++ );// prints 1
    t1.equals( t3 );
    System.out.println( count++ );// prints 2
    t3.equals( o1 );
    System.out.println( count++ );// prints 3
    t3.equals(t3);
    System.out.println( count++ );// prints 4
    t3.equals(t2);
  }
}
