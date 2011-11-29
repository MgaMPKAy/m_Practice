public class BookBTree {
	public static void main(String[] args) {
		BTree<Book> bt = new BTree<Book>();

		Book b;
		for (int i = 0; i < 200; i++) {
			b = new Book("A", "B", "C", 10);
			System.out.println(b.id);
			bt.add(b);
		}

		for (int i = 1; i < 200; i++) {
			b = new Book();
			b.setId(i);
			System.out.println(bt.contains(b));
			
		}
		for (int i = 1; i < 200; i++) {
			b = new Book();
			b.setId(i);
			bt.remove(b);
			
		}

		
	}
}