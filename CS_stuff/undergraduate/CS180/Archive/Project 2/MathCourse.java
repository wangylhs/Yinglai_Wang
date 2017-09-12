import cs.Course;
import java.lang.String;
    
public class MathCourse implements Course
{
    public String CourseName;
    public String CourseNo;
    public String CourseTitle;
    public String Subject;
    public String Grade;
    public double Final_Score;
        
    public String calculateGrade(int attendance, int homeWorkScore, int examScore)
    {
        Final_Score = (attendance*20/100) + (homeWorkScore*40/100) + (examScore*40/100);
        
        if(Final_Score >= 80)
        {
            return "A";
        }
        
        else if(Final_Score >= 60 && Final_Score <80)
        {
            return "B";
        }
        
        else if(Final_Score <60)
        {
            return "C";
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