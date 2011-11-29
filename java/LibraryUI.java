import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;
import java.util.regex.*;
import java.util.ArrayList;

public class LibraryUI {

	JFrame mainFrame;
	Container mainContentPane;
	Box topBox;
	JToolBar toolBar;
	JPanel searchPanel;
	JTextField searchField;
	JButton searchButton;
	JTable resultTable;
	LibraryToolBarActions libActions;
	// TODO: Replace ArrayList with BTree;
	ArrayList<Book> library = new ArrayList<Book>();

	LibraryUI () {
		mainFrame = new JFrame("Library");
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.setPreferredSize(new Dimension(800, 600));
		mainContentPane = mainFrame.getContentPane();

		topBox = new Box(BoxLayout.Y_AXIS);
		mainContentPane.add(topBox);

		libActions = new LibraryToolBarActions(this);
		
		toolBar = new JToolBar();
		toolBar.add(libActions.addAction);
		toolBar.add(libActions.searchAction);
		toolBar.add(libActions.editAction);
		toolBar.add(libActions.borrowAction);
		topBox.add(toolBar);

		searchPanel = new JPanel();
		searchPanel.setLayout(new BorderLayout());
		searchPanel.setMaximumSize(new Dimension(800, 35));
		searchButton = new JButton(libActions.searchAction);
		searchButton.setText("Search");
		searchField = new JTextField();
		searchPanel.add(searchButton, BorderLayout.EAST);
		searchPanel.add(searchField, BorderLayout.CENTER);
		topBox.add(searchPanel);

		Object[] columName = {"ID", "Name", "Author", "Press", "Count"}; 
		DefaultTableModel tableModel = new DefaultTableModel(columName, 0);
		resultTable = new JTable(tableModel);
		JScrollPane scrollPane = new JScrollPane(resultTable);
		topBox.add(scrollPane);
		
		mainFrame.pack();
		mainFrame.setVisible(true);
	}

	public static void main(String[] args) {
		LibraryUI libUI = new LibraryUI();
	}

	void buildEditFrame() {
		JFrame frame = new JFrame();
		frame.add(new JLabel("ad"));
		frame.setPreferredSize(new Dimension(400, 300));
		frame.pack();
		frame.toFront();
		frame.setVisible(true);
	}

	void buildBorrowFrame() {
	
	}

	void buildAddFrame() {
		JFrame frame = new JFrame();
		frame.add(new JLabel("ad"));
		frame.setPreferredSize(new Dimension(400, 300));
		frame.pack();
		frame.toFront();
		frame.setVisible(true);
	}
}

class LibraryToolBarActions {
	LibraryUI libUI;

	LibraryToolBarActions(LibraryUI libUI) {
		this.libUI = libUI;
	}

	Action searchAction = new AbstractAction("Add", new ImageIcon("img/refresh.png")) {
		public void actionPerformed(ActionEvent e) {

			DefaultTableModel tm = (DefaultTableModel)libUI.resultTable.getModel();
			tm.setRowCount(0);

			String queryString = libUI.searchField.getText();
			for (Book book : libUI.library) {
				if (book.match(queryString)) {
					tm.addRow(book.toJTableRow());
				}
			}
		}
	};

	Action borrowAction = new AbstractAction("Borrow", new ImageIcon("img/borrow.png")) {
		public void actionPerformed(ActionEvent e) {
			libUI.buildBorrowFrame();
		}
	};


	Action editAction = new AbstractAction("Edit", new ImageIcon("img/edit.png")) {
		public void actionPerformed(ActionEvent e) {
			int row = libUI.resultTable.getSelectedRow();
			Integer idI = (Integer)libUI.resultTable.getValueAt(row, 0);
			int id = idI.intValue();
			System.out.println(id);
			new EditFrame(libUI, id);
		}
	};

	Action addAction = new AbstractAction("Add", new ImageIcon("img/add.png")) {
		public void actionPerformed(ActionEvent e) {
			new AddFrame(libUI);
		}
	};

}

class AddFrame {
	
	LibraryUI libUI;
	JFrame frame		= new JFrame();
	JPanel panel		= new JPanel();
	JTextField nameFiled	= new JTextField();
	JTextField authorFiled	= new JTextField();
	JTextField pressFiled	= new JTextField();
	JTextField countFiled	= new JTextField();
	
	AddFrame(LibraryUI libUI) {
		this.libUI = libUI;
	
		frame.setPreferredSize(new Dimension(400, 240));
	
		nameFiled.setPreferredSize(new Dimension(200, 30));
		authorFiled.setPreferredSize(new Dimension(200, 30));
		pressFiled.setPreferredSize(new Dimension(200, 30));
		countFiled.setPreferredSize(new Dimension(200, 30));

		JLabel nameLabel	= new JLabel("Name");
		JLabel authorLabel	= new JLabel("author");
		JLabel pressLabel	= new JLabel("Press");
		JLabel countLabel	= new JLabel("Count");
		authorLabel.setPreferredSize(new Dimension(100, 30));
		nameLabel.setPreferredSize(new Dimension(100, 30));
		countLabel.setPreferredSize(new Dimension(100, 30));
		pressLabel.setPreferredSize(new Dimension(100, 30));
		
		panel.setLayout(new FlowLayout());
		panel.add(nameLabel);
		panel.add(nameFiled);
		panel.add(authorLabel);
		panel.add(authorFiled);
		panel.add(pressLabel);
		panel.add(pressFiled);
		panel.add(countLabel);
		panel.add(countFiled);
		
		Container cp = frame.getContentPane();
		cp.add(panel, BorderLayout.CENTER);

		panel = new JPanel(new FlowLayout());
		JButton addButton = new JButton(addFrameAction);
		JButton cancelButton = new JButton(cancelAction);
		
		addButton.setPreferredSize(new Dimension(120, 30));
		cancelButton.setPreferredSize(new Dimension(120, 30));
		panel.add(addButton);
		panel.add(cancelButton);
		cp.add(panel, BorderLayout.SOUTH);
		
		frame.pack();
		frame.toFront();
		frame.setVisible(true);
	}

	Action addFrameAction = new AbstractAction("Add", new ImageIcon("img/add.png")) {
		public void actionPerformed(ActionEvent e) {
			String name = nameFiled.getText();
			String author = authorFiled.getText();
			String press = pressFiled.getText();
			int count = Integer.parseInt(countFiled.getText());
			Book newBook = new Book(name, author, press, count);
			newBook.toFile();
			libUI.library.add(newBook);
			frame.setVisible(false);
			frame.dispose();
		}
	};

	Action cancelAction =  new AbstractAction("Cancel", new ImageIcon("img/add.png")) {
		public void actionPerformed(ActionEvent e) {
			frame.setVisible(false);
			frame.dispose();
		}
	};
}

class EditFrame {
	LibraryUI libUI;
	Book book;
	
	JFrame frame		= new JFrame();
	JPanel panel		= new JPanel();
	JTextField nameFiled	= new JTextField();
	JTextField authorFiled	= new JTextField();
	JTextField pressFiled	= new JTextField();
	JTextField countFiled	= new JTextField();
	
	EditFrame(LibraryUI libUI, int id) {
		this.libUI = libUI;
		this.book = Book.fromFile(id);
			
		frame.setPreferredSize(new Dimension(400, 240));
	
		nameFiled.setPreferredSize(new Dimension(200, 30));
		authorFiled.setPreferredSize(new Dimension(200, 30));
		pressFiled.setPreferredSize(new Dimension(200, 30));
		countFiled.setPreferredSize(new Dimension(200, 30));

		nameFiled.setText(book.name);
		authorFiled.setText(book.author);
		pressFiled.setText(book.press);
		countFiled.setText("" + book.count);
		
		JLabel nameLabel	= new JLabel("Name");
		JLabel authorLabel	= new JLabel("Author");
		JLabel pressLabel	= new JLabel("Press");
		JLabel countLabel	= new JLabel("Count");
		authorLabel.setPreferredSize(new Dimension(100, 30));
		nameLabel.setPreferredSize(new Dimension(100, 30));
		countLabel.setPreferredSize(new Dimension(100, 30));
		pressLabel.setPreferredSize(new Dimension(100, 30));
		
		panel.setLayout(new FlowLayout());
		panel.add(nameLabel);
		panel.add(nameFiled);
		panel.add(authorLabel);
		panel.add(authorFiled);
		panel.add(pressLabel);
		panel.add(pressFiled);
		panel.add(countLabel);
		panel.add(countFiled);
		
		Container cp = frame.getContentPane();
		cp.add(panel, BorderLayout.CENTER);

		panel = new JPanel(new FlowLayout());
		JButton addButton = new JButton(addFrameAction);
		JButton cancelButton = new JButton(cancelAction);
		
		addButton.setPreferredSize(new Dimension(120, 30));
		cancelButton.setPreferredSize(new Dimension(120, 30));
		panel.add(addButton);
		panel.add(cancelButton);
		cp.add(panel, BorderLayout.SOUTH);
		
		frame.pack();
		frame.toFront();
		frame.setVisible(true);
	}

	Action addFrameAction = new AbstractAction("Add", new ImageIcon("img/add.png")) {
		public void actionPerformed(ActionEvent e) {
			String name = nameFiled.getText();
			String author = authorFiled.getText();
			String press = pressFiled.getText();
			int count = Integer.parseInt(countFiled.getText());
			book.setName(name);
			book.setAuthor(author);
			book.setPress(press);
			book.setCount(count);
			book.toFile();
			frame.setVisible(false);
			frame.dispose();
		}
	};

	Action cancelAction =  new AbstractAction("Cancel", new ImageIcon("img/cancle.png")) {
		public void actionPerformed(ActionEvent e) {
			frame.setVisible(false);
			frame.dispose();
		}
	};
}
