public class BookBTree {
	public static void main(String[] args) {
		BTree<Book> bt = new BTree<Book>();

		Book b;
		for (int i = 0; i < 15; i++) {
			b = new Book("A", "B", "C", 10);
			bt.add(b);
		}

		for (int i = 1; i < 15; i++) {
			b = new Book();
			b.setId(i);
			System.out.println(bt.contains(b));
			
		}
		for (int i = 14; i >= 0; i--) {
			b = new Book();
			b.setId(i);
			bt.remove(b);
			
		}

		System.out.println("Get test");
		Book bget1 = new Book("Adlezz", "B", "c", 101);
		bt.add(bget1);
		Book bget2 = bt.get(bget1);
		bget2.setName("Zelda");

		bt.update(bget2);
		for (int i = 0; i < 30; i++) {
			b = new Book("A", "B", "C", 10);
			bt.add(b);
		}

		Book bget3 = bt.get(bget1);
		System.out.println(bget3.name);		
	}
}