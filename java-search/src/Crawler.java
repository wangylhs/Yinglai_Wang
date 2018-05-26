import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.io.*;
import java.net.*;
import java.util.regex.*;
import java.sql.*;
import java.util.*;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.UIManager;

import org.jsoup.Jsoup;
//import org.apache.commons.lang3.StringEscapeUtils;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class Crawler
{
	Connection connection;
	int urlID;
	public Properties props;
	static int maxurls;
	int NextURLID;
	int NextURLIDScanned;
	static String jdbcurl, jdbcuser, jdbcpass, root, domain;
	static JFrame frame;
	static JPanel main;
	static JPanel left;
	static JPanel right;
	static JLabel jdbc_url, jdbc_username, jdbc_password, jdbc_maxurls, jdbc_domain, jdbc_root;
	static JLabel d_url, d_username, d_password, d_maxurls, d_domain, d_root;



	Crawler() {
		urlID = 0;
	}

	public void readProperties() throws IOException {
		props = new Properties();
		FileInputStream in = new FileInputStream("database.properties");
		props.load(in);
		in.close();
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

	public void createDB() throws SQLException, IOException {
		openConnection();

		Statement stat = connection.createStatement();

		// Delete the table first if any
		try {
			stat.executeUpdate("DROP TABLE URLS");
		}catch( Exception e) {
		}
		try {
			stat.executeUpdate("DROP TABLE WORDS");
		}catch( Exception e) {
		}	
		// Create the table
		stat.executeUpdate("CREATE TABLE URLS (urlid INT, url VARCHAR(512), description VARCHAR(200), image VARCHAR(200))");
		stat.executeUpdate("CREATE TABLE WORDS (word VARCHAR(200), urlid INT)");
	}

	public boolean urlInDB(String urlFound) throws SQLException, IOException {
		Statement stat = connection.createStatement();
		ResultSet result = stat.executeQuery( "SELECT * FROM urls WHERE url LIKE '"+urlFound+"'");
		if (result.next()) {
			//System.out.println("URL "+urlFound+" already in DB");
			return true;
		}
		// System.out.println("URL "+urlFound+" not yet in DB");
		return false;
	}
	
	public void insertURLInDB(String url) throws SQLException, IOException {
		Statement stat = connection.createStatement();
		String query = "INSERT INTO urls VALUES ('"+NextURLID+"','"+url+"','','')";
		//System.out.println("Executing "+query);
		stat.executeUpdate( query );
		urlID++;
	}
	
	public boolean wordInDB(String word) throws SQLException, IOException{
		Statement stat = connection.createStatement();
		ResultSet result = stat.executeQuery("SELECT * FROM words WHERE word LIKE '"+word+"'");
		if(result.next()){
			System.out.println("WORD "+word+" already in DB");
			return true;
		}
		// System.out.println("WORD "+word+" not yet in DB");
		return false;
	}
	
	public void insertWORDInDB(String word, int word_urlid) throws SQLException, IOException {
		Statement stat = connection.createStatement();
		String query = "INSERT INTO words VALUES ('"+word+"','"+word_urlid+"')";
		stat.executeUpdate( query );
		//System.out.println(word + " " + word_urlid);
	}
	
	public void updateWordInDB(String word, String word_urlid) throws SQLException, IOException{
		Statement stat = connection.createStatement();
		String query = "UPDATE words SET urlid='"+word_urlid+"' WHERE word='"+word+"'";
		//System.out.println(word + " " + word_urlid);
		stat.executeUpdate( query );
	}
	
	public void getWord(String desc, int urlid) throws SQLException, IOException{
		String txt = desc.replaceAll("[^A-Za-z0-9\\s]+", "");
		List<String> wordlist = Arrays.asList(txt.split("\\s+"));
		Set<String> wordset = new HashSet<String>(wordlist);
		for(String word : wordset){
			
			if(word.length()<200) insertWORDInDB(word, urlid);
		}
	}
	
	public boolean isWeb(String urlFound){
		if(urlFound.indexOf("cs.purdue")==-1) return false; 
        if(urlFound.length()==0) return false;
        if(urlFound.indexOf("ftp")>=0) return false;
        if(urlFound.indexOf("mailto")>=0) return false;
        
        int index = urlFound.indexOf('#');
        if( index >= 0)
            urlFound = urlFound.substring(0, index);
        index = urlFound.lastIndexOf('.');
        if( index > 0){
            String suffix = urlFound.substring(index+1, urlFound.length());
            if (suffix.equalsIgnoreCase("pdf"))
                return false;
            if(suffix.equals("shtml"))
                return false;
            if(suffix.equals("pptx"))
                return false;
            if(suffix.equalsIgnoreCase("jpg"))
                return false;
            if(suffix.equals("gif") || suffix.equals("png") || suffix.equals("jpeg") || suffix.equals("bmp"))
                return false;
            if(suffix.equals("mp3"))
                return false;
            if(suffix.equals("au"))
                return false;
            if(suffix.equals("lsl"))
                return false;
            if(suffix.equals("PDF"))
                return false;
            if(suffix.equals("rtf"))
            	return false;
            if(suffix.equals("doc"))
                return false;
            if(suffix.equals("docx"))
                return false;
            if(suffix.equals("txt"))
                return false;
            if(suffix.equals("ppt"))
                return false;
            if(suffix.equals("mp4")|| suffix.equals("avi") || suffix.equals("mpg") || suffix.equals("wmv") || suffix.equals("flv")|| suffix.equals("mov"))
                return false;
            if(suffix.equals("xz"))
                return false;
            if(suffix.equals("bz2"))
                return false;
            if(suffix.equals("ps"))
                return false;
            if(suffix.equals("wrz"))
                return false;
            if(suffix.equals("wrl"))
                return false;
            if(suffix.equals("v"))
                return false;
            if(suffix.equals("gz"))
                return false;
            if(suffix.equals("Z"))
                return false;
            if(suffix.equals("swf"))
                return false;
            if(suffix.equals("zip") || suffix.equals("tar") || suffix.equals("tgz"))
                return false;
            if(suffix.equals("cpp") || suffix.equals("c") || suffix.equals("java") || suffix.endsWith("py"))
            	return false;
        }
        return true;

	}
	

	public void crawl(){
		try{
		Statement stmt = connection.createStatement();
        while (NextURLIDScanned < NextURLID && NextURLIDScanned<maxurls) {
             ResultSet results = stmt.executeQuery("SELECT * FROM urls WHERE urlid LIKE '"+NextURLIDScanned+"'");
            if(!results.next()){
                NextURLIDScanned++;
                continue;
            }
            String curUrl = results.getString(2);
            Document doc;
            String dscrpt;
            Elements images;
            Element img = null;
            String imgurl  = "https://www.cs.purdue.edu/images/brand.svg";;
            try{
                doc = Jsoup.connect(curUrl).timeout(10000).followRedirects(true).get();
                images = doc.getElementsByTag("img");
                dscrpt = doc.text();
            }catch(Exception e){
                NextURLIDScanned++;
                continue;
            }

             //  Get the first 100 characters or less of the document from url1 without tags. Add this description to the URL record in the URL table.
            dscrpt = dscrpt.replaceAll("[^A-Za-z0-9\\s]+", "");
            String dsp;
            if(dscrpt.length()>180){
                dsp = dscrpt.substring(0,180);
            }
            else{
                dsp = dscrpt.substring(0,dscrpt.length());
            }
            //remove images that are icons, buttons, logo and brand
            Iterator itr = images.iterator();
            String str="";
            while(itr.hasNext()){
            	img = (Element) itr.next();
            	str = img.absUrl("src");
            	if(str.contains("logo")||str.contains("brand")||
            			str.contains("icons")||str.contains("button")||str.contains("buttons")||
            			str.contains("Icons")||str.contains("Button")||str.contains("Buttons")||
            			str.contains("'")){
            		itr.remove();
            	}
            }
            
            if(images.size()>0){
            	img = images.first();
            	imgurl = img.absUrl("src");
            }
            stmt.executeUpdate( "UPDATE urls SET description = '"+dsp+"' WHERE urlid LIKE '"+NextURLIDScanned+"'");
            stmt.executeUpdate("UPDATE urls SET image = '"+imgurl+"' WHERE urlid LIKE '"+NextURLIDScanned+"'");
            System.out.println(NextURLIDScanned);
            
            if(NextURLID < maxurls){
                 Elements links = doc.select("a[href]");
                for (Element link : links){
                    if(NextURLID >= maxurls)
                        break;
                    String urlFound = link.absUrl("href");
                    urlFound = urlFound.replaceAll("'", "");
                    
                    if(!isWeb(urlFound)) continue;
                    if (NextURLID < maxurls && !urlInDB(urlFound)){
                        insertURLInDB(urlFound);
                        NextURLID++;
                    }
                }
            }
            //System.out.println("NextURLIDScanned:"+NextURLIDScanned+"\n, NextURLID:"+NextURLID);
            // Get the document in url1 without tags
            getWord(dscrpt,NextURLIDScanned);
            NextURLIDScanned++;
            if(NextURLIDScanned>=maxurls) connection.close();
            
        }
		}catch(Exception e){
			e.printStackTrace();
		}
        
	}
	
	public void startCrawl() throws SQLException, IOException{
		NextURLID = 0;
		NextURLIDScanned = 0;
		urlID = NextURLID;
		createDB();
		insertURLInDB(root);
		NextURLID++;
		//System.out.println(root);
		crawl();
	}
	
	public static void createFrame(){
		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        frame.setTitle("Data base properties");
        createLabel();
        createPanel();
        frame.add(main);
        frame.setLocation(500, 400);
        frame.setSize(400, 500);
        frame.setResizable(false);
	}
	
	public static void createPanel(){
		main = new JPanel(new BorderLayout());
		left = new JPanel(new GridLayout(6,1));
		left.add(jdbc_url);
		left.add(jdbc_username);
		left.add(jdbc_password);
		left.add(jdbc_maxurls);
		left.add(jdbc_domain);
		left.add(jdbc_root);
		right = new JPanel(new GridLayout(6,1));
		right.add(d_url);
		right.add(d_username);
		right.add(d_password);
		right.add(d_maxurls);
		right.add(d_domain);
		right.add(d_root);
		main.add(left, BorderLayout.WEST);
		main.add(right, BorderLayout.EAST);
		
	}
	
	public static void createLabel(){
		jdbc_url = new JLabel("\tjdbc.url:");
		jdbc_username = new JLabel("  jdbc.username:");
		jdbc_password = new JLabel("  jdbc.password:");
		jdbc_maxurls = new JLabel("  crawler.maxurls:");
		jdbc_domain = new JLabel("  crawler.domain:");
		jdbc_root = new JLabel("  crawler.root:");
		d_url = new JLabel(jdbcurl);
		d_username = new JLabel(jdbcuser);
		d_password = new JLabel(jdbcpass);
		d_maxurls = new JLabel(Integer.toString(maxurls));
		d_domain = new JLabel(domain);
		d_root = new JLabel(root);
		
	}
	
	public static void showDialog(){
		JOptionPane.showMessageDialog(null, "Crawler finished crawl " + maxurls + " urls", "Complete", JOptionPane.INFORMATION_MESSAGE);
	}

	public static void main(String[] args)
	{
		Crawler crawler = new Crawler();

		try {
			crawler.readProperties();
			crawler.root = crawler.props.getProperty("crawler.root");
			crawler.jdbcurl = crawler.props.getProperty("jdbc.url");
			crawler.jdbcuser = crawler.props.getProperty("jdbc.username");
			crawler.jdbcpass = crawler.props.getProperty("jdbc.password");
			crawler.maxurls = Integer.parseInt(crawler.props.getProperty("crawler.maxurls"));
			crawler.domain = crawler.props.getProperty("crawler.domain");
			createFrame();
			crawler.startCrawl();
			showDialog();
			
		}
		catch( Exception e) {
			e.printStackTrace();
		}
	}
}

