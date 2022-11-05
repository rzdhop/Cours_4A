import java.net.*;
import java.io.*;

public class bruteForce{

	public static void main(String []args){
		int webPort = 80;
		String payload = "";
		Socket senderSocket = null;
		boolean foundToken = false;
		try 
		{
			System.out.printf("Starting bruteforce !\n");
			String []pageFound = new String[999];
			
			for(int i=0; i< 999; i++){
				senderSocket = new Socket("localhost", webPort);
				OutputStream out = senderSocket.getOutputStream();
				BufferedReader in = new BufferedReader(new InputStreamReader(senderSocket.getInputStream()));
				payload = String.format("GET /%d.cgi HTTP/1.1\r\nHost: localhost\r\nConnection: Close\r\n\r\n", i);
				System.out.printf("TESTING %s.cgi --> ", i);
				out.write(payload.getBytes());
				out.flush();
				
				String head = in.readLine();
				//HTTP/1.0 404 ....
				System.out.printf("CODE : %s \r", head.split(" ")[1]);
				if(head.split(" ")[1].equals("200")){
					pageFound[i] = "Found";
				}
				in.close();
			}

			for(int i = 0; i < pageFound.length; i++){
				if(pageFound[i] == "Found"){
					System.out.printf("\n\t%s.cgi Found !", i);
					foundToken = true;
				}
			}
			if(!foundToken){
				System.out.printf("No Pages found !");
			}
			//senderSocket.close();
		}
		catch(IOException e){
			System.err.printf("\nerror : %s", e);
		}
	}
}
