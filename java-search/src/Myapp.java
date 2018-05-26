import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.net.*;
import java.util.*;
import java.sql.*;
import java.util.regex.*;
import java.util.Arrays;
import java.util.Comparator;

public class Myapp extends HttpServlet {
	private static final long serialVersionUID = 1L;
	PrintWriter out;
	public Properties props;
	Connection connection;
	class Result implements Comparator<Result>, Comparable<Result>{
		private int id;
		private int freq;
		Result(){ }
		Result(int a, int b){
			id = a;
			freq = b;
		}
		public int getURLID(){
			return id;
		}
		@Override
		public int compareTo(Result r) {
			return 0;
		}
		@Override
		public int compare(Result r1, Result r2) {
			return r1.freq-r2.freq;
		}
		
	}
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.setContentType("text/html");
		out = response.getWriter();
		out.println("<html>");
		out.println("<header>");
		out.println("<style>p {color:gray}  </style>");
		out.println("<title><center>MySearch</center></title>");
		out.println("</header>");
		out.println("<body>");
		out.println("<center><h1>My Search</h1>");
		out.println("<p> Please enter Keyword: </p>");
		String kw =new String();
		kw = request.getParameter("keyword");
		
		//out.println("<P>");
		out.print("<form action=\"");
		out.print("Myapp\" ");
		out.println("method=POST>");
		out.println("<p>keyword:");
		out.println("<input type=text size=100 name=keyword></p>");
		out.println("<br>");
		out.println("<input type=submit size=50 value=Search>");
		out.println("</form></center>");
		if (kw != null) {
			out.println("<p style=\"color:blue\">Search Result for ");
			out.println(HTMLFilter.filter(kw) +
					"</p>");
		} else {
			//out.println("No keywords, Please enter some");
		}
		if(kw!=null){
			String[] keywords=kw.split(" ");
			out.println("<div style=\"margin-left: 10px;\">");
			if(keywords.length>1){
				multi_keyword(keywords);
			}
			else{
				single_keyword(kw);
			}
		}
		out.println("</div>");
		out.println("</body>");
		out.println("</html>");

	}

	public void multi_keyword(String[] keywords){

		try {
			Class.forName("com.mysql.jdbc.Driver");
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
						out.println("<div style=\"clear: left;\">");
						out.println("<div> <p style=\"float: left;\"> " +
								"<img src= \"" + urls.getString("image") + "\"" +
								"style=\"width:200px;height:250px\" border=\"1px\"></p>");
						out.println(" <a href=\""+urls.getString("url")+"\">"+urls.getString("url")+"</a><br>");		
						out.println("<p>"+urls.getString("description")+"<br>" +"</p></div>");
					}
				}
			}
			if(!totalfound){
				for(int i=0;i<keywords.length;i++){
					single_keyword(keywords[i]);
				}
			}
			stmt.close();

		}
		catch(Exception e){
			out.println(e.getMessage()+"<br>");
			e.printStackTrace();
		}

	}
	public void single_keyword(String kw){
		try {
			Class.forName("com.mysql.jdbc.Driver");
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
			//rank urls based on the frequency of keyword
			List<Result> ranked_url = new ArrayList<Result>();
			int count=0;
			while (itr.hasNext()) {
				int urlid = (int) itr.next();
				
				ResultSet r = stmt.executeQuery("SELECT COUNT(*) FROM WORDS WHERE word LIKE '"+ kw +
						"' and urlid LIKE '" + urlid +"'");
				while(r.next()){
					ranked_url.add(new Result(urlid, Integer.parseInt(r.getString(1))));
					//System.out.println(r.getString(1));
				}
				/*
				ResultSet urls = stmt.executeQuery("SELECT * FROM URLS WHERE urlid LIKE '"+urlid+"'");
				while (urls.next()){
					out.println("<div style=\"clear: left;\">");
					out.println("<div> <p style=\"float: left;\"> " +
							"<img src= \"" + urls.getString("image") + "\"" +
							"style=\"width:200px;height:250px\" border=\"1px\"></p>");
					out.println(" <a href=\""+urls.getString("url")+"\">"+urls.getString("url")+"</a><br>");		
					out.println("<p>"+urls.getString("description")+"<br>" +"</p></div>");
				}
                 */
			}
			
			Collections.sort(ranked_url, new Result());
			for(Result a: ranked_url){
				int urlid = a.getURLID();
				ResultSet urls = stmt.executeQuery("SELECT * FROM URLS WHERE urlid LIKE '"+urlid+"'");
				while(urls.next()){
				out.println("<div style=\"clear: left;\">");
				out.println("<div> <p style=\"float: left;\"> " +
						"<img src= \"" + urls.getString("image") + "\"" +
						"style=\"width:200px;height:250px\" border=\"1px\"></p>");
				out.println(" <a href=\""+urls.getString("url")+"\">"+urls.getString("url")+"</a><br>");		
				out.println("<p>"+urls.getString("description")+"<br>" +"</p></div>");
				}
			}
			
			stmt.close();
		}
		catch(Exception e){
			out.println(e.getMessage()+"<br>");
			e.printStackTrace();
		}
	}

	public void openConnection() throws SQLException, IOException
	{
		String drivers = "jdbc.drivers";
		if (drivers != null) System.setProperty("jdbc.drivers", drivers);
		String url = "jdbc:mysql://localhost:8888/CRAWLER";
		String username = "root";
		String password = "database";
		connection = DriverManager.getConnection( url, username, password);
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
