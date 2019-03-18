import java.net.*;
import java.io.*;

public class EchoServer
{
	public static void main(String[] args) {
		try {
			int portNum = 6013;
			ServerSocket sock = new ServerSocket(portNum);
			
			/* now listen for connections */
			while (true)
			{
				Socket client = sock.accept();
				BufferedReader bfr = new BufferedReader(new InputStreamReader(client.getInputStream()));
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				
				
				/* write the Data to the socket */
				int i;
				char c;
				
				do
				{
					i = bfr.read();
					c = (char)i;
					pout.print(c);
				}
				while((i != -1) && (c != '\n'));
				pout.println();
				
				/* close the socket and resume */
				/* listening for connections */
				client.close();
			}
		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
	}
}
