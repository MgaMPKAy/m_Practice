import java.io.*;
import java.util.regex.*;
import java.util.ArrayList;

public class Book implements Comparable, Serializable {
	String name, author, press;
	int id, count;
	ArrayList<String> borrowers;
	static int idCount;
	
	Book() {
		borrowers = new ArrayList<String>();
	}

	Book(String name, String author, String press, int count) {
		id		= ++idCount;
		this.name	= name;
		this.author	= author;
		this.press	= press;
		this.count	= count;
		this.borrowers	= new ArrayList<String>(count);
	}
	
	void setName(String name) {
		this.name = name;
	}

	void setAuthor(String name) {
		this.author = author;
	}

	void setPress(String name) {
		this.name = name;
	}

	void setId(int id) {
		this.id = id;
	}

	void setCount(int count) {
		this.count = count;
	}
	
	public int compareTo(Object that) {
		
		return ((Book)that).id - this.id;
	}
	
	Object[] toJTableRow() {
		Object[] row = {id, name, author, press, count};
		return row;
	}

	boolean boorowTO(String newBorrower) {
		if (borrowers.contains(newBorrower))
		    return false;
		borrowers.add(newBorrower);
		return true;
	}

	boolean returnFrom(String borrower) {
		if (!borrowers.contains(borrower))
			return false;
		borrowers.remove(borrower);
		return true;
	}

	boolean match(String query) {
		Pattern pattern = Pattern.compile(".*" + query.toLowerCase() + ".*");
		Matcher matcher;
		boolean isMathch;

		String[] fields = {name, author, press};
		for (String field : fields) {
			matcher = pattern.matcher(field.toLowerCase());
			isMathch = matcher.matches();
			if (isMathch) {
				return isMathch;
			}
		}
		return false;
	}

	static Book fromFile(int id) {
		try {
			ObjectInputStream in =
				new ObjectInputStream(new FileInputStream("book-" + id));
			return (Book)(in.readObject());
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
			return null;
		}
	}

	void toFile() {
		try {
			ObjectOutputStream out =
				new ObjectOutputStream(new FileOutputStream("book-" + id));
			out.writeObject(this);
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}