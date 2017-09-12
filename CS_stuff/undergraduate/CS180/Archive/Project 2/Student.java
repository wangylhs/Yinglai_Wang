import java.util.Scanner;

import cs.IStudent;
import cs.University;

/**
 * Project 2
 * <description>
 * @author <yourname>
 *
 */
public class Student implements IStudent {

	/* Make sure that setName() is called */
	private String name;
	private University purdue = new University();

	public void populateStudentData() {
		Scanner in = new Scanner(System.in);
		System.out.print("Enter Name  :: ");
		this.setName(in.next());
	}

	public static void main(String args[]) {
		Student student1 = new Student();
		student1.populateStudentData();

	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
}
