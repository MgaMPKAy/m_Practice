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

	public BTree<Book> library = new BTree<Book>();
	// ArrayList<Book> library = new ArrayList<Book>();
	
	
	

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
			// for (Book book : libUI.library) {
			// 	if (book.match(queryString)) {
			// 		tm.addRow(book.toJTableRow());
			// 	}
			// }
			// BTreeNode node = BTreeNode.readFromDisk(rootId);
			
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

