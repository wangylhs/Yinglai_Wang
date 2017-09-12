import cs.Course;
import java.lang.String;

public class CSCourse implements Course
{
    public String CourseName;
    public String CourseNo;
    public String CourseTitle;
    public String Subject;
    public String Grade;
    public double Final_Score;

    public String calculateGrade(int attendance, int homeWorkScore, int examScore)
    {
        Final_Score = (attendance*10/100) + (homeWorkScore*60/100) + (examScore*30/100);

        if(Final_Score >= 75)
        {
            return "A";
        }

        else if(Final_Score >= 65 && Final_Score <75)
        {
            return "B";
        }

        else if(Final_Score >= 55 && Final_Score <65)
        {
            return "C";
        }
        
        else if(Final_Score <55)
        {
            return "D";
        }

        return "Error: Grade Caulcation Problem";
    }

    //Accessors
    public String getCourseName()
    {
        return CourseName;
    }

    public String getCourseNo()
    {
        return CourseNo;
    }

    public String getCourseTitle()
    {
        return CourseTitle;
    }

    public String getSubject()
    {
        return Subject;
    }

    //Mutators

    public void setCourseName(String name)
    {
        CourseName = name;
    }

    public void setCourseNo(String num)
    {
        CourseNo = num;
    }

    public void setCourseTitle(String Title)
    {
        CourseTitle = Title;
    }

    public void setSubject(String subject)
    {
        Subject = subject;
    }
}