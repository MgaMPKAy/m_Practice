import java.io.*;

class IdGenerator {

	public static File FILE = new File(BTree.DIR + "id");

	public static int nextId() {
		try {
			int result;
			if (FILE.exists()) {
				ObjectInputStream in =
					new ObjectInputStream(new FileInputStream(FILE));
				result = in.readInt();
			} else {
				result = 0;
			}
			ObjectOutputStream out =
				new ObjectOutputStream(new FileOutputStream(FILE));
			out.writeInt(result + 1);
			out.close();
			return result;
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
			return 0;
		}
	}

	public static void main(String[] args) {
		System.out.println(nextId());
	}
}

class BookIdGenerator extends IdGenerator {
	public static File FILE = new File(BTree.DIR + "bookId");
}