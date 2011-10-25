import java.net.*;
import java.util.*;
import java.io.*;

public class EchoServer implements Runnable {
	private ServerSocket server;

	EchoServer(int portNumber) {
		try {
			server = new ServerSocket(portNumber);
			if (server != null) {
				new Thread(this).start();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void run() {
		while (true) {
			try {
				Socket client = server.accept();
				System.out.println("accepted");
				new ClientHandler(client);
			} catch (Exception e) {
				
			}
		}
	}

	public static void main(String[] args) {
		EchoServer server = new EchoServer(8080);
	}
}

class ClientHandler implements Runnable {
	Socket client;

	ClientHandler(Socket client) {
		this.client = client;
		new Thread(this).start();
	}

	public void run() {
		PrintWriter out		= null;
		BufferedReader in	= null;
		while (true) {
			try {
				out = new PrintWriter(client.getOutputStream(), true);
				in = new BufferedReader(new InputStreamReader(client.getInputStream()));
				while (true) {
					String line = in.readLine();
					if (line != null) {
						System.out.println(line);
						out.println(line);
					} else {
						client.close();
						return ;
					}

				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
}