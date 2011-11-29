public class Game {
	public static void main(String[] args) {
		LibraryUI libUI = new LibraryUI();
		libUI.library.add(new Book("Book1", "Adlezz", "AdlezzPress", 10));
		libUI.library.add(new Book("Book2", "zzelda", "zzeldaPress", 10));
		libUI.library.add(new Book("Book3", "zzelda", "zzeldaPress", 10));
		libUI.library.add(new Book("Book4", "zzelda", "zzeldaPress", 10));
		libUI.library.add(new Book("koob5", "Adlezz", "AdlezzPress", 10));
		libUI.library.add(new Book("koob6", "Adlezz", "zzeldaPress", 10));
	}
}