import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import util.HTMLFilter;

import java.net.*;
import java.util.regex.*;
import java.sql.*;
import java.util.*;

public class myapp extends HttpServlet {
    static String root;
    Connection connection;
    public Properties props;
	String domain = "cs.purdue.edu";
    int maxurls;
    PrintWriter out;
 public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException
    {
        response.setContentType("text/html");
        out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title><center>Search Engine</center></title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<center><h1>Search Engine</h1>");
        out.println("Please enter Keyword:<br>");
        String kw =new String();
        kw = request.getParameter("keyword");
        if (kw != null) {
            out.println("keyword");
            out.println(" = " + HTMLFilter.filter(kw) +
                        "<br>");
        } else {
            out.println("No keywords, Please enter some");
        }

        
        out.println("<P>");
        out.print("<form action=\"");
        out.print("myapp\" ");
        out.println("method=POST>");
        out.println("keyword:");
        out.println("<input type=text size=20 name=keyword>");
        out.println("<br>");
        out.println("<input type=submit value=Search>");
        out.println("</form></center>");
        
        if(kw!=null){
        String[] keywords=kw.split(" ");
        out.println("<div style=\"margin-left: 100px;\">");
        if(keywords.length>1){
            morewords(keywords);
        }
        else{
            oneword(kw);
        }
        }
        out.println("</div>");
        out.println("</body>");
        out.println("</html>");
    }
    
    public void morewords(String[] keywords){
      /*  for(int i=0;i<keywords.length;i++){
        out.println("keyword: "+keywords[i]+"<br>");
        }*/
        try {
            Class.forName("com.mysql.jdbc.Driver");
            readProperties();
            openConnection();
            Statement stmt = connection.createStatement();
            ResultSet[] rs = new ResultSet[keywords.length];
            List<Integer>[] list =new List[keywords.length];
            for(int i=0;i<keywords.length;i++){
                list[i]= new LinkedList<Integer>();
            }
            
            for(int i=0;i<keywords.length;i++){
                rs[i] = stmt.executeQuery("SELECT * FROM WORDS WHERE word LIKE '"+keywords[i]+"'");
                while (rs[i].next())
                {
                    // out.println(rs.getInt("urlid")+"<br>");
                    list[i].add(rs[i].getInt("urlid"));
                }

            }
            Iterator itr = list[0].iterator();
            
            boolean totalfound=false;
            while (itr.hasNext()){
                int urlid = (int) itr.next();
                boolean found=true;
                for(int i=0;i<keywords.length;i++){
                    if(list[i].contains(urlid))
                        continue;
                    else{
                        found=false;
                    }
                }
                if(found){
                    totalfound=true;
                    ResultSet urls = stmt.executeQuery("SELECT * FROM URLS WHERE urlid LIKE "+urlid);
                    while (urls.next()){
                        postlink(urls.getString("url"));
                        out.println(urls.getString("description")+"<br><br>");
                    }
                }
            }
            if(!totalfound){
                for(int i=0;i<keywords.length;i++){
                    oneword(keywords[i]);
                }
            }
                stmt.close();
           
        }
        catch(Exception e){
            out.println(e.getMessage()+"<br>");
            e.printStackTrace();
        }

    }

    public void oneword(String kw){
        try {
            Class.forName("com.mysql.jdbc.Driver");
            readProperties();
            openConnection();
            Statement stmt = connection.createStatement();
            
            ResultSet rs = stmt.executeQuery("SELECT * FROM WORDS WHERE word LIKE '"+kw+"'");
            
            
            if (!rs.next()){
                //out.println("no result");
            }
            List<Integer> list = new LinkedList<Integer>();
            while (rs.next())
            {
                // out.println(rs.getInt("urlid")+"<br>");
                list.add(rs.getInt("urlid"));
            }
            Iterator itr = list.iterator();
            while (itr.hasNext()) {
                int urlid = (int) itr.next();
                ResultSet urls = stmt.executeQuery("SELECT * FROM URLS WHERE urlid LIKE "+urlid);
                while (urls.next()){
                    postlink(urls.getString("url"));
                    out.println(urls.getString("description")+"<br><br>");
                }
            }
            
            stmt.close();
		}
        catch(Exception e){
            out.println(e.getMessage()+"<br>");
            e.printStackTrace();
        }
    }
    public void postlink(String link)
    {
        out.println(" <a href=\""+link+"\">"+link+"</a><br>");
        
    }
   
    
    public void doPost(HttpServletRequest request, HttpServletResponse res)
    throws IOException, ServletException
    {
        doGet(request, res);
    }
    
    public void openConnection() throws SQLException, IOException
	{
		String drivers = props.getProperty("jdbc.drivers");
        if (drivers != null) System.setProperty("jdbc.drivers", drivers);
        
        String url = props.getProperty("jdbc.url");
        String username = props.getProperty("jdbc.username");
        String password = props.getProperty("jdbc.password");
        connection = DriverManager.getConnection( url, username, password);
    }
    public void readProperties() throws IOException {
        props = new Properties();
        FileInputStream in = new FileInputStream("database.properties");
        props.load(in);
        in.close();
	}
    


}