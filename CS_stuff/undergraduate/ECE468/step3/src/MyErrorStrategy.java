import org.antlr.v4.runtime.*;

class MyErrorStrategy extends DefaultErrorStrategy{

    public void reportError(Parser recognizer,  RecognitionException e){
        System.out.println(e.getOffendingToken());
        System.out.println("Not accepted");
        System.exit(1);
    }
    
	protected void reportUnwantedToken(Parser recognizer)
    {
	    System.out.println("Not Accepted");
	    System.exit(0);
    }
    
    
}