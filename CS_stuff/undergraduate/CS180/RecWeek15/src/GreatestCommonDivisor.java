public class GreatestCommonDivisor
{
    public int gCD(int x, int y)
    {
    	if(y==0)
    		return x;
    	else
    		return gCD(y, x%y);
    }
    
    public static void main(String args[])
    {
    	GreatestCommonDivisor gcd = new GreatestCommonDivisor();
    	System.out.print(gcd.gCD(4,6));
    }
}