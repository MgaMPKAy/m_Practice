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

		} catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("Please specific an IP address");
		} catch (ConnectException e) {
			System.out.println("Can't connect to specificed server");
		} catch (Exception e) {
			e.printStackTrace();
		}

	}
}