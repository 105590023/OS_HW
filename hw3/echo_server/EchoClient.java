import java.net.*;
import java.io.*;

public class EchoClient
{
	public static void main(String[] args) {
		try {
			/* make connection to server socket */
			int portNum = 6013;
			Socket sock = new Socket("127.0.0.1", portNum);
			BufferedReader bin = new BufferedReader(new InputStreamReader(sock.getInputStream()));
			PrintWriter pout = new PrintWriter(sock.getOutputStream(), true);
			BufferedReader inputData = new BufferedReader(new InputStreamReader(System.in));
			
			/* send the data to the socket */
			String line;
			line = inputData.readLine();
			pout.println(line);
			
			/* read the data from the socket */
			int i;
			char c;
			
			do
			{
				i = bin.read();
				c = (char)i;
				System.out.print(c);
			}
			while((c != '\n') && (i != -1));
			
			/* close the socket connection*/
			sock.close();
		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
	}
}
