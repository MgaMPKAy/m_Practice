import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;
import java.util.regex.*;
import java.util.ArrayList;

public class LibraryUI {

	private JFrame mainFrame;
	private Container mainContentPane;
	private Box topBox;
	private JToolBar toolBar;
	private JPanel searchPanel;
	private JButton searchButton;
	private LibraryToolBarActions libActions;
	
	public JTextField searchField;
	public JTable	 resultTable;

	public BTree<Book> library;
	
	LibraryUI () {
		setupLibrary();
		
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
		DefaultTableModel tm = (DefaultTableModel)resultTable.getModel();
		tm.setRowCount(0);
		ArrayList<Book> al = library.toArrayList();
		for (Book book : al) {
			tm.addRow(book.toJTableRow());
		}
		topBox.add(scrollPane);
		
		mainFrame.pack();
		mainFrame.setVisible(true);
	}

	public static void main(String[] args) {
		LibraryUI libUI = new LibraryUI();
	}

	
	protected void setupLibrary() {
		File datafile = new File(BTree.DIR + "btree");
		if (datafile.exists()) {
			library = BTree.readFromDisk();
		} else {
			library = new BTree<Book>();
		}
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
			libUI.setupLibrary();
			ArrayList<Book> al = libUI.library.toArrayList();
			for (Book book : al) {
				if (book.match(queryString)) {
					tm.addRow(book.toJTableRow());
				}
			}
		}
	};

	Action borrowAction = new AbstractAction("Borrow", new ImageIcon("img/borrow.png")) {
		public void actionPerformed(ActionEvent e) {
			// new BorrowFrame();
		}
	};


	Action editAction = new AbstractAction("Edit", new ImageIcon("img/edit.png")) {
		public void actionPerformed(ActionEvent e) {
			int row = libUI.resultTable.getSelectedRow();
			Integer idI = (Integer)libUI.resultTable.getValueAt(row, 0);
			int id = idI.intValue();
			new EditFrame(libUI, id);
		}
	};

	Action addAction = new AbstractAction("Add", new ImageIcon("img/add.png")) {
		public void actionPerformed(ActionEvent e) {
			new AddFrame(libUI);
		}
	};

}

