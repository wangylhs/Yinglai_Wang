
import org.antlr.v4.runtime.*;

class Errorhandler extends DefaultErrorStrategy
{
   public void reportError(Parser re, RecognitionException e)
   {
        System.out.println("Not Accepted");
        System.exit(0); 
   }
     
    protected void reportUnwantedToken(Parser re)
    {
	    System.out.println("Not Accepted");
	    System.exit(0); 
    }

}