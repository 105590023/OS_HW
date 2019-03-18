import java.net.*;
import java.io.*;

public class filecopy
{
	public static void main(String[] args)
	{
		try
		{
			BufferedReader inFile = new BufferedReader(new FileReader(args[0]));
			PipedOutputStream out = new PipedOutputStream();
			PipedInputStream in = new PipedInputStream(out);
				
			Thread WritePipe = new Thread(new Runnable()
			{
			   	public void run()
			   	{
			   		try
			   		{
			   			String line;
			   			byte[] newLine = {'\n'};
			   			while((line = inFile.readLine()) != null)
						{
							out.write(line.getBytes());
							out.write(newLine);
						}
						out.close();
			   		}
			   		catch(IOException ioe)
			   		{
			   			System.err.println(ioe);
			   		}
			   	}
			});
			
			Thread ReadPipe = new Thread(new Runnable()
			{
		        public void run()
		        {
		            try {
		            	FileOutputStream os = new FileOutputStream(args[1]);
		            	int data;
		            	while((data = in.read()) != -1)
				        {
				        	char c = (char)data;
				        	String str = String.valueOf(c);
				        	os.write(str.getBytes());
				        }
		                os.close();
		            }
		            catch(IOException ioe)
			   		{
			   			System.err.println(ioe);
			   		}
		        }
		    });
			
			WritePipe.start();
			ReadPipe.start();
		}
		catch(IOException ioe)
		{
			System.err.println(ioe);
		}
	}
}
