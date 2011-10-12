import java.net.*;
import java.io.*;
import java.util.*;

class EchoClient {
	public static void main(String[] args) {
		Socket client		= null;
		PrintWriter out		= null;
		BufferedReader in	= null;
		Scanner sc		= new Scanner(System.in);

		try {
			client	= new Socket(args[0], 8080);
			out	= new PrintWriter(client.getOutputStream(), true);
			in	= new BufferedReader(new InputStreamReader(client.getInputStream()));


			while (true) {
				String line = sc.next();
				if (line.equals("BYE")) break;
				out.println(line);
				String response = in.readLine();
				System.out.println(response);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}

	}
}