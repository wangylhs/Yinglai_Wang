import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;
import java.util.Timer;
import java.util.TimerTask;



public class iClickerServer
{
  public static void main( String args[] ){
		ServerSocket s;
		try{
			s = new ServerSocket(12345);
			int i = 1;
			while( true ){
				Socket incoming = s.accept();
				System.out.println("Spawing " + i);
				Runnable r = new ThreadHandler(incoming);
				Thread t = new Thread(r);
				t.start();
				i++;
			}
			//t.join();
			//s.close();
		}catch(IOException e1){
			e1.printStackTrace();
		}
	}

}

class ThreadHandler implements Runnable
{


	public static Connection getConnection() throws SQLException, IOException
   	{
      	Properties props = new Properties();
      	FileInputStream in = new FileInputStream("database.properties");
      	props.load(in);
      	in.close();
		
		String drivers = props.getProperty("jdbc.drivers");
		if(drivers != null)
			System.setProperty("jdbc.drivers",drivers);
      	String url = props.getProperty("jdbc.url");
      	String username = props.getProperty("jdbc.username");
      	String password = props.getProperty("jdbc.password");
		//System.out.println("url="+url+" user="+username+" password="+password);
      	return DriverManager.getConnection(url,username,password);
   	}

	private Socket clientSocket;
	private static int qid = -1;
	private static Object sb = null ;
	private static Timer timer = new Timer();
	private static TimerTask timetask;
	private static String question = null;
	public ThreadHandler( Socket client ){
		clientSocket = client;
	}

  	private void studentClient( String[] args , DataOutputStream out , Connection conn )
   	{
  	   	if( args[1].compareTo("submit") == 0 ){
  	   		if( qid == -1 ){
  	   			System.out.println("submit permission denied");
  	   			return;
  	   		}
			String username = args[2];
			String answer = args[4];

			try{
				Statement state = conn.createStatement();
				ResultSet resultset = state.executeQuery("select * from Q"+qid+" where username="+"'"+username+"';");
				boolean hasUsername = resultset.next();
				if( hasUsername ){
					state.executeUpdate("update Q"+qid+" set answer='"+answer+"' where username='"+username+"';");
				}else{
					state.executeUpdate("insert into Q"+qid+" values('"+username+"','"+answer+"');");
				}
				
			}catch( Exception e ){
				
			}
	   	}else if( args[1].compareTo("register") == 0 ){
	   		System.out.println("register attemp detected");
			String username = args[2];
			String password = args[3];
			
			try {
				Statement state = conn.createStatement();
				ResultSet resultset = state.executeQuery("select * from Student where username="+"'"+username+"';");
				boolean hasUsername = resultset.next();
				if( hasUsername ){
					out.writeChars("1\n");
				}else{
					state.executeUpdate("insert into Student values('" + username + "' , '" + password + "');");
					out.writeChars("0\n");
				}
				
			} catch (SQLException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
			
	    }else if( args[1].compareTo("login") == 0 ){
	    	System.out.println("login attemp detected");
	    	String username = args[2];
	    	String password = args[3];
	    	System.out.println(username+"|"+password);
	    	Statement state;
			try {
				state = conn.createStatement();
				ResultSet result = state.executeQuery("select * from Student where username='"+username+"' && password='"+password+"';");
				boolean isCorrect = result.next();
				if( isCorrect ){
					out.writeChars("0\n");
				}else{
					out.writeChars("1\n");
				}
				
			} catch (SQLException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
   		}else if( args[1].compareTo("getquestion") == 0 ){
//  	   		if( qid == -1 )
 // 	   			return;
   			System.out.println("student getquestion");
			try{
				out.writeChars(question+" |");

			}catch( Exception e ){
				
			}
	   	}
  	   	
	    else{
   			System.out.println("invalid student command");
		
		}
  	}
	
	private void adminClient( String[] args , DataOutputStream out , Connection conn )
	{
		if( args[1].compareTo("login") == 0 ){
			String username = args[2];
			String password = args[3];
			try {
				Statement state = conn.createStatement();
				ResultSet resultset = state.executeQuery("select * from Admin where username='"+username+"' && password='"+password+"';");
				boolean isCorrect = resultset.next();
				if( isCorrect ){
					out.writeInt(0);
				}else{
					out.writeInt(1);
				}
				
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}else if( args[1].compareTo("start") == 0 ){
			if( qid != -1 )
				return;
			qid = Integer.parseInt(args[2]);
			
			String quizID = args[3];
			
			timetask = new TimerTask(){
				public void run() {
					qid = -1;
					System.out.println("Time Out");
				}				
			};
			timer.schedule(timetask, Long.parseLong(args[4])*1000);
			try {
				Statement state = conn.createStatement();
				System.out.println("connected");
				ResultSet resultset = state.executeQuery("select * from Question where questionID="+qid);
				boolean hasQuestion = resultset.next();
				if( hasQuestion ){
					state.executeUpdate("update Question set quizID="+quizID+" where questionID="+qid+";");
					state.executeUpdate("drop table Q"+qid+";");
				}else{
					state.executeUpdate("insert into Question values("+qid +","+quizID +");");
				}
				state.executeUpdate("create table Q"+qid+" (username varchar(20),answer varchar(50),unique(username));");
				
				
			} catch (SQLException e) {
				e.printStackTrace();
			} 
			
	    }else if( args[1].compareTo("stop") == 0 ){
	   		qid = -1;
	   		timetask.cancel();
	   		System.out.println("stop");
	   		
     	}else if( args[1].compareTo("answercount") == 0 ){
     		System.out.println("admin answercount");
	      	String questionID = args[2];
	      	try {
				Statement state = conn.createStatement();
				int count;
				ResultSet result = state.executeQuery("select * from Q" + questionID +" where " + "answer='A'");
				count = 0;
				while(result.next())count++;
				out.writeInt(count);
			
				System.out.print(count+"|");
				result = state.executeQuery("select * from Q" + questionID +" where " + "answer='B'");
				count = 0;
				while(result.next())count++;
				out.writeInt(count);
				
				System.out.print(count+"|");
				result = state.executeQuery("select * from Q" + questionID +" where " + "answer='C'");
				count = 0;
				while(result.next())count++;
				out.writeInt(count);
				
				System.out.print(count+"|");
				result = state.executeQuery("select * from Q" + questionID +" where " + "answer='D'");
				count = 0;
				while(result.next())count++;
				out.writeInt(count);
				
				System.out.print(count+"|");
				result = state.executeQuery("select * from Q" + questionID +" where " + "answer='E'");
				count = 0;
				while(result.next())count++;
				out.writeInt(count);
				System.out.println(count);
				
			} catch (SQLException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
	    }else if( args[1].compareTo("submitlist") == 0 ){
	   		
    		String questionID =args[2];
    		Statement state;
			try {
				state = conn.createStatement();
				ResultSet result = state.executeQuery("select * from Q"+questionID+";");
				while(result.next()){
					out.writeChars(result.getString(1)+"|"+result.getString(2)+"\n");
				}
			} catch (SQLException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}	
      	}else{
    	}
	}
	private void getQuestion( DataInputStream in ){
		char lastChar = ' ';
		char temp = ' ';
		question = "";
		while( true ){
			try {
				temp = in.readChar();
				question = question + temp;
				if( temp == '\n' && lastChar == '\n' )break;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			lastChar = temp;
		}
		System.out.println(question);
	}
	private void handleRequest( InputStream in , OutputStream out )
	{
		DataInputStream input = new DataInputStream(in);
		DataOutputStream output = new DataOutputStream(out);
		
		Connection conn=null;
		try{
			conn = getConnection();
			
			String request = "";
			char temp;
			while( (temp = input.readChar()) != '\n'  ){
				request = request + temp;
			}

			String[] args = request.split("\\|");
			if( args[0].compareTo("student") == 0  ){		
				studentClient(args,output,conn);
			}else if( args[0].compareTo("admin") == 0 ){
				adminClient(args,output,conn);
			}else if( args[0].compareTo("admins") == 0 ){
				getQuestion(input);
			}else{
				
			}
			
			System.out.println("thread end");
		}catch(Exception e){
			e.printStackTrace();
		}finally{
			try{
				
				if(conn != null) conn.close();
			}catch(Exception e){
				
			}
		}
		
	}

	public void run(){
			try{
				InputStream inStream = clientSocket.getInputStream();
				OutputStream outStream = clientSocket.getOutputStream();
				handleRequest(inStream,outStream);
				clientSocket.close();
			}catch(IOException e1){
		
			}finally{

			}
	}
}

