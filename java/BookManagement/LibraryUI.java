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
	public DefaultTableModel tableModel;
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

		JPanel toolBarPanel = new JPanel(new FlowLayout());
		toolBarPanel.setMaximumSize(new Dimension(800,35));
		toolBarPanel.add(new JButton(libActions.addAction));
		toolBarPanel.add(new JButton(libActions.searchAction));
		toolBarPanel.add(new JButton(libActions.editAction));
		toolBarPanel.add(new JButton(libActions.borrowAction));
		toolBarPanel.add(new JButton(libActions.returnAction));
		toolBarPanel.add(new JButton(libActions.delAction));
		topBox.add(toolBarPanel);

		searchPanel = new JPanel();
		searchPanel.setLayout(new BorderLayout());
		searchPanel.setMaximumSize(new Dimension(800, 35));
		searchButton = new JButton(libActions.searchAction);
		searchField = new JTextField();
		searchPanel.add(searchButton, BorderLayout.EAST);
		searchPanel.add(searchField, BorderLayout.CENTER);
		topBox.add(searchPanel);

		Object[] columName = {"ID", "书名", "作者", "出版社", "馆藏"};
		tableModel = new DefaultTableModel(columName, 0);
		resultTable = new JTable(tableModel);
		JScrollPane scrollPane = new JScrollPane(resultTable);
		tableModel.setRowCount(0);
		ArrayList<Book> al = library.toArrayList();
		refresh();
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

 	public void refresh() {
		tableModel.setRowCount(0);
		String queryString = searchField.getText();
		setupLibrary();
		ArrayList<Book> al = library.toArrayList();
		for (Book book : al) {
			if (book.match(queryString)) {
				tableModel.addRow(book.toJTableRow());
			}
		}
	}

}

class LibraryToolBarActions {
	LibraryUI libUI;

	LibraryToolBarActions(LibraryUI libUI) {
		this.libUI = libUI;
	}

	Action searchAction = new AbstractAction("查找", new ImageIcon("img/find.png")) {
		public void actionPerformed(ActionEvent e) {
			libUI.tableModel.setRowCount(0);
			libUI.refresh();
		}
	};

	Action borrowAction = new AbstractAction("借书", new ImageIcon("img/borrow.png")) {
		public void actionPerformed(ActionEvent e) {
			int row = libUI.resultTable.getSelectedRow();
			if (row < 0) return;

			Integer idI = (Integer)libUI.resultTable.getValueAt(row, 0);
			new BorrowFrame(libUI, idI.intValue());
			libUI.refresh();
		}
	};

	Action returnAction = new AbstractAction("还书", new ImageIcon("img/return.png")) {
		public void actionPerformed(ActionEvent e) {
			int row = libUI.resultTable.getSelectedRow();
			if (row < 0) return;

			Integer idI = (Integer)libUI.resultTable.getValueAt(row, 0);
			new ReturnFrame(libUI, idI.intValue());
		}
	};


	Action editAction = new AbstractAction("编辑", new ImageIcon("img/edit.png")) {
		public void actionPerformed(ActionEvent e) {
			int row = libUI.resultTable.getSelectedRow();
			if (row < 0) return;

			Integer idI = (Integer)libUI.resultTable.getValueAt(row, 0);
			new EditFrame(libUI, idI.intValue());
		}
	};

	Action addAction = new AbstractAction("增加", new ImageIcon("img/add.png")) {
		public void actionPerformed(ActionEvent e) {
			new AddFrame(libUI);
		}
	};

	Action delAction = new AbstractAction("删除", new ImageIcon("img/del.png")) {
		public void actionPerformed(ActionEvent e) {
			int row = libUI.resultTable.getSelectedRow();
			if (row < 0) return;

			Integer idI = (Integer)libUI.resultTable.getValueAt(row, 0);
			Book delBook = new Book();
			delBook.setId(idI.intValue());
			libUI.library.remove(delBook);

			libUI.tableModel.removeRow(row);
		}
	};

}

