import java.net.*;
import java.io.*;
import java.util.Random;

public class QOTD_Server
{
    public static void main(String[] args) {
        try {
            ServerSocket sock = new ServerSocket(6017);

            /* now listen for connections */
            while (true)
            {
                Socket client = sock.accept();
                PrintWriter pout = new
                PrintWriter(client.getOutputStream(), true);

                /* write the Date to the socket */
                pout.println(ReadQuote());

                /* close the socket and resume */
                /* listening for connections */
                client.close();
            }
        }
        catch (IOException ioe) {
            System.err.println(ioe);
        }
    }

	public static String ReadQuote()
	{
		String quote[] = {
			"The time will never be just right.",
			"You can't buy happiness.",
			"Don't quit your day dream.",
			"Never give up.",
			"Be kind but not weak."
		};
		Random ran = new Random();
		return quote[ran.nextInt(5)];
	}
}
