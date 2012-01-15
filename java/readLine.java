class readLine {
	static String readLine(){
		int ch;
		String s = "";

		while (true) {
			try {
				ch = System.in.read();
				if (ch == -1 || (char)ch == '\n') {
					break;
				} else if ((char)ch != '\r') {
					s += (char)ch;
				}
			} catch (IOException e) {

			}
		}
		return s;
	}
}
			