package team.n13.iClicker;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.regex.Pattern;
import team.n13.iClicker.R;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.StrictMode;
import android.view.Gravity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Toast;

public class Login extends Activity {
	
	private EditText getUser; //Takes username from the user
	private EditText getPass; //Takes password from the user
	private CheckBox rememberPass;
	public final static String SERVER_PATH = "sslab14.cs.purdue.edu"; //server path stored here
	private Button bLogin; //Login button
	private Button bRegister; //Register button
	public static String userLogin; //The valid username entered by the user
	public static String userPass; //The valid username entered by the user
	private Intent intent;
	public static Activity here;	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.login);
		
		StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
		StrictMode.setThreadPolicy(policy);

		here=this;
		
		getUser = (EditText) findViewById(R.id.etUsername);
		getPass = (EditText) findViewById(R.id.etPassword);
		rememberPass = (CheckBox) findViewById(R.id.cbRememberPassword);
		rememberPass.setText(R.string.Login_rememberPassword);
		
		try {
		
		    BufferedReader inputReader = new BufferedReader(new InputStreamReader(
		            openFileInput("Username")));
		
		    String inputString;
		
		    StringBuffer stringBuffer = new StringBuffer();                
		
		    while ((inputString = inputReader.readLine()) != null) {
		
		        stringBuffer.append(inputString);
		
		    }
		
		    getUser.setText(stringBuffer.toString());
		    
		    inputReader = new BufferedReader(new InputStreamReader(
		            openFileInput("Password")));
		    
		    inputString="";
			
		    stringBuffer = new StringBuffer();
		    
		    while ((inputString = inputReader.readLine()) != null) {
		        stringBuffer.append(inputString);
		    }
		
		    getPass.setText(stringBuffer.toString());
		    
		    inputReader = new BufferedReader(new InputStreamReader(
		            openFileInput("isRememberPassword")));
		    
		    inputString="";
			
		    stringBuffer = new StringBuffer();
		    
		    while ((inputString = inputReader.readLine()) != null) {
		        stringBuffer.append(inputString);
		    }
		
		    System.out.printf("My state: %s\n", stringBuffer.toString());
		    
		    if(stringBuffer.toString().equals("1"))
		    	rememberPass.setChecked(true);
		    else{
		    	rememberPass.setChecked(false);
		    }
		
		} catch (IOException e) {
		
		    e.printStackTrace();
		
		}
		 
		rememberPass.setOnClickListener(new OnClickListener() {
		  public void onClick(View v) {
	        //is Remember password checked?
			if (((CheckBox) v).isChecked()) {
				Toast.makeText(Login.this, "The password has been remembered.", Toast.LENGTH_SHORT).show();
			}
		  }
		});
		
		bLogin = (Button) findViewById(R.id.bLogin);
		bLogin.setText(R.string.login);
		bLogin.setOnClickListener(new OnClickListener() {
			
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String tmpUser=getUser.getText().toString();
				String tmpPass=getPass.getText().toString();
				Toast display;	
				boolean b = Pattern.compile("\\p{Alnum}+").matcher(tmpUser).matches(); // Regex accepting ASCII only
				if(tmpUser.equals("") || !b )
				{
					display = Toast.makeText(Login.this,getString(R.string.Login_validUser), Toast.LENGTH_SHORT);
					display.setGravity(Gravity.CENTER, 0, 0);
					display.show();
				}
				else if(tmpPass.equals(""))
				{
					display = Toast.makeText(Login.this,getString(R.string.Login_validPass), Toast.LENGTH_SHORT);
					display.setGravity(Gravity.CENTER, 0, 0);
					display.show();
				}
				
				else
				{
					userLogin = String.valueOf(tmpUser);
					userPass = String.valueOf(tmpPass);
					
					String data = "student|login"+"|"+userLogin+"|"+userPass+"\n";
					
					/*display = Toast.makeText(Login.this,"This is what I am sending:\n"+data, Toast.LENGTH_LONG);
					display.show();*/
					
					String ret = "";
					try {
				         Socket skt = new Socket(SERVER_PATH,12345);
				         System.out.print("Client has connected!\n");
				         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
				         System.out.print("Sending string: " + data + "\n");
				         out.writeChars(data);
				     	//reading the return value from server
				         DataInputStream in = new DataInputStream(skt.getInputStream());
					    	System.out.print("Received string: ");

					    	 char temp;
					         while ( (temp = in.readChar()) != '\n' ){
					        	 System.out.println(temp);
					        	 ret += temp; // Read one line and output it
					         }

					         System.out.print("\n");
					         in.close();
					         out.close();
					         skt.close();
				      }
				      catch(Exception e) {
				         System.out.print("Whoops! It didn't work!\n");
				      }

					
					/*display = Toast.makeText(Login.this,"This is what I have: "+ret, Toast.LENGTH_SHORT);
					display.show();*/
					
					//checking the return value
					if(ret.equals("0")){
						try {

						    FileOutputStream fos = openFileOutput("Username", Context.MODE_PRIVATE);

						    fos.write(userLogin.getBytes());

						    fos.close();
						    
						    if(rememberPass.isChecked()){
							    fos = openFileOutput("Password", Context.MODE_PRIVATE);

							    fos.write(userPass.getBytes());

							    fos.close();
							    
							    fos = openFileOutput("isRememberPassword", Context.MODE_PRIVATE);

							    fos.write("1".getBytes());

							    fos.close();
						    }
						    else{
							    fos = openFileOutput("Password", Context.MODE_PRIVATE);

							    fos.write("".getBytes());

							    fos.close();
							    
							    fos = openFileOutput("isRememberPassword", Context.MODE_PRIVATE);

							    fos.write("0".getBytes());

							    fos.close();
						    }
						} catch (Exception e) {

						    e.printStackTrace();

						}
						display = Toast.makeText(Login.this,"You have succesfully logged in.", Toast.LENGTH_SHORT);
						display.show();
						ret="";
						String question="";
						try {
					         Socket skt = new Socket(Login.SERVER_PATH,12345);
					         data = "student|getquestion\n";
					         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
					         System.out.print("Sending string: " + data + "\n");
					         out.writeChars(data);
					         //reading the return value from server
							 DataInputStream in = new DataInputStream(skt.getInputStream());
							 
						     System.out.print("Received string: ");

					    	 char temp;
					         while ( (temp = in.readChar()) != '|' ){
					        	 question += temp; // Read one line and output it
					         }

					         System.out.printf("%s\n", question);
						     out.close();
						     in.close();
						     skt.close();
						} catch (UnknownHostException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						
						 if(question.equals(null) && (question.indexOf("A.") == -1 || question.indexOf("B.") == -1)){
							 	Intent intent=new Intent();
								intent.setClass(Login.this,team.n13.iClicker.student.FreeResponse.class);
							    if(!rememberPass.isChecked())
							    	getPass.setText("");
								startActivity(intent);
						 }
						 else{
						intent=new Intent();
						intent.setClass(Login.this,team.n13.iClicker.student.SubmitAnswer.class);
					    if(!rememberPass.isChecked())
					    	getPass.setText("");
						startActivity(intent);
						 }
					}else if(ret.equals("1")){
						display = Toast.makeText(Login.this,"Incorrect username or password.", Toast.LENGTH_SHORT);
						display.show();
						ret="";
					}
				}
			}
		});
		
		bRegister = (Button) findViewById(R.id.bRegister);
		bRegister.setText(R.string.register);
		bRegister.setOnClickListener(new OnClickListener() {
			
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String tmpUser=getUser.getText().toString();
				String tmpPass=getPass.getText().toString();
				Toast display;	
				boolean b = Pattern.compile("\\p{Alnum}+").matcher(tmpUser).matches(); // Regex accepting ASCII only
				if(tmpUser.equals("") || !b )
				{
					display = Toast.makeText(Login.this,getString(R.string.Login_validUser), Toast.LENGTH_SHORT);
					display.setGravity(Gravity.CENTER, 0, 0);
					display.show();
				}
				else if(tmpPass.equals(""))
				{
					display = Toast.makeText(Login.this,getString(R.string.Login_validPass), Toast.LENGTH_SHORT);
					display.setGravity(Gravity.CENTER, 0, 0);
					display.show();
				}
				
				else
				{
					userLogin = String.valueOf(tmpUser);
					userPass = String.valueOf(tmpPass);
					String data = "student|register"+"|"+userLogin+"|"+userPass+"\n";
					/*display = Toast.makeText(Login.this,"This is what I am sending:\n"+data, Toast.LENGTH_LONG);
					display.show();*/
					String ret = "";
					try {
				         Socket skt = new Socket(SERVER_PATH, 12345);
				         System.out.print("Client has connected!\n");
				         DataOutputStream out = new DataOutputStream(skt.getOutputStream());
				         System.out.print("Sending string: " + data + "\n");
				         out.writeChars(data);
				     	 //reading the return value from server
				         DataInputStream in = new DataInputStream(skt.getInputStream());
					     System.out.print("Received string: ");

					    	 char temp;
					         while ( (temp = in.readChar()) != '\n' ){
					        	 System.out.println(temp);
					        	 ret += temp; // Read one line and output it
					         }

					         System.out.print("\n");
					     in.close();
					     out.close();
				         skt.close();
				      }
				      catch(Exception e) {
				         System.out.print("Whoops! It didn't work!\n");
				      }
					
					/*display = Toast.makeText(Login.this,"This is what I have: "+ret, Toast.LENGTH_SHORT);
					display.show();*/
					
					//checking the return value
					if(ret.equals("0")){
						display = Toast.makeText(Login.this,"You have been succesfully registered. You may now login using your username and password.", Toast.LENGTH_SHORT);
						display.show();
					}else if(ret.equals("1")){
						display = Toast.makeText(Login.this,"Duplicate username! You may try a different user name.", Toast.LENGTH_SHORT);
						display.show();
					}
				}
			}
		});
	}
}