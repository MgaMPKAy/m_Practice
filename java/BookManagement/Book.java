import java.io.*;
import java.util.regex.*;
import java.util.ArrayList;

public class Book implements Comparable, Serializable {
	public String name, author, press;
	public int id, count;
	public ArrayList<String> borrowers;
	public static int idCount;

	Book() {
		borrowers = new ArrayList<String>();
		id = 0;
	}

	Book(String name, String author, String press, int count) {
		id		= BookIdGenerator.nextId();
		this.name	= name;
		this.author	= author;
		this.press	= press;
		this.count	= count;
		this.borrowers	= new ArrayList<String>(count);
	}

	void setName(String name) {
		this.name = name;
	}

	void setAuthor(String author) {
		this.author = author;
	}

	void setPress(String press) {
		this.press = press;
	}

	void setId(int id) {
		this.id = id;
	}

	void setCount(int count) {
		this.count = count;
	}

	void update(String name, String author, String press, int count) {
		this.name = name;
		this.author = author;
		this.press = press;
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

	public String toString() {
		return "Book " + id + ": " + name;
	}
}