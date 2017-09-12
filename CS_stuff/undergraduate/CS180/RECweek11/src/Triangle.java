
public class Triangle implements SimpleGeometry {
	public static void main(String[] args){
		Triangle triangle = new Triangle();
		Point a = new Point(0,0);
		Point b = new Point(1,0);
		Point c = new Point(1,1);
		double tolerance = 0.1*Math.pow(10, -6);
		double length = triangle.length(a, b);
		
		System.out.println("Length from a to b: " + length);
		System.out.println("Right Triangle: " + triangle.RightAngledTriangle(a, b, c, tolerance));
		System.out.println("Isosceles Triangle: " + triangle.isoscelesTriangle(a, b, c, tolerance));
		
	}
	public Triangle(){
		
	}
	public double length(Point P, Point Q){
		double length = 0;
		length = Math.sqrt(Math.pow(Q.getX()-P.getX(), 2) + Math.pow(Q.getY()-P.getY(),2));
		return length;
	}
	public boolean RightAngledTriangle(Point P, Point Q, Point R, double tolerance){
		double d1 = length(P,Q);
		double d2 = length(P,R);
		double d3 = length(Q,R);
		if(d1 - Math.sqrt(d2*d2+d3*d3) < tolerance){
			return true;
		}
		return false;
	}
	public boolean isoscelesTriangle(Point P, Point Q, Point R, double tolerance){
		double d1 = length(P,Q);
		double d2 = length(P,R);
		double d3 = length(Q,R);
		
		if(Math.abs(d2-d1)<tolerance && Math.abs(d3-d1)<tolerance && Math.abs(d2-d3)<tolerance){
			return true;
		}
		return false;
	}
	
}
interface SimpleGeometry{
	public double length(Point P, Point Q);
	public boolean RightAngledTriangle(Point P, Point Q, Point R, double tolerance);
	public boolean isoscelesTriangle(Point P, Point Q, Point R, double tolerance);
}
class Point{
	private double x;
	private double y;
	
	public Point(){
		x = 0.0;
		y = 0.0;
	}
	public Point(double x, double y){
		this.x = x;
		this.y = y;
	}
	public double getX(){
		return x;
	}
	public double getY(){
		return y;
	}
}
