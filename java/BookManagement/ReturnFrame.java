import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;
import java.util.ArrayList;

class ReturnFrame {

	LibraryUI libUI;
	Book book;
	JFrame frame		= new JFrame();
	JPanel panel		= new JPanel();
	JTextField nameFiled	= new JTextField();
	JTextField authorFiled	= new JTextField();
	JTextField pressFiled	= new JTextField();
	JTextField countFiled	= new JTextField();
	DefaultTableModel tableModel;
	JTable borrowerTable;

	ReturnFrame(LibraryUI libUI, int id) {
		this.libUI = libUI;
		Book originBook = new Book();
		originBook.setId(id);
		book = libUI.library.get(originBook);

		ArrayList<String> borrowers = book.borrowers;

		frame.setPreferredSize(new Dimension(400, 240));

		Container cp = frame.getContentPane();
		JLabel label = new JLabel("选择姓名");
		cp.add(label, BorderLayout.NORTH);

		Object[] columName = {"姓名"};
		tableModel = new DefaultTableModel(columName, 0);
		borrowerTable = new JTable(tableModel);

		Object[] objs = borrowers.toArray();
		for (Object obj: objs) {
			Object[] row = {obj};
			tableModel.addRow(row);
		}
		JScrollPane scrollPane = new JScrollPane(borrowerTable);
		cp.add(scrollPane, BorderLayout.CENTER);

		panel = new JPanel(new FlowLayout());
		JButton returnButton = new JButton(returnFrameAction);
		JButton cancelButton = new JButton(cancelAction);

		returnButton.setPreferredSize(new Dimension(120, 30));
		cancelButton.setPreferredSize(new Dimension(120, 30));
		panel.add(returnButton);
		panel.add(cancelButton);
		cp.add(panel, BorderLayout.SOUTH);

		frame.pack();
		frame.toFront();
		frame.setVisible(true);
	}

	Action returnFrameAction = new AbstractAction("还书", new ImageIcon("img/return.png")) {
		public void actionPerformed(ActionEvent e) {
			int row = borrowerTable.getSelectedRow();
			String name = (String)borrowerTable.getValueAt(row, 0);
			ArrayList<String> tmp = new ArrayList<String>();
			for (String borrower : book.borrowers) {
				if (!borrower.equals(name)) {
					tmp.add(borrower);
				}
			}
			book.borrowers = tmp;
			book.count++;
			libUI.library.update(book);
			libUI.refresh();

			frame.setVisible(false);
			frame.dispose();
		}
	};

	Action cancelAction =  new AbstractAction("取消", new ImageIcon("img/cancel.png")) {
		public void actionPerformed(ActionEvent e) {
			frame.setVisible(false);
			frame.dispose();
		}
	};
}