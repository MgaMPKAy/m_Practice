import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;
import java.util.ArrayList;

class BorrowFrame {

	LibraryUI libUI;
	Book book;
	JFrame frame		= new JFrame();
	JPanel panel		= new JPanel();
	JTextField nameFiled	= new JTextField();
	DefaultTableModel tableModel;
	JTable borrowerTable;

	BorrowFrame(LibraryUI libUI, int id) {
		this.libUI = libUI;
		Book originBook = new Book();
		originBook.setId(id);
		book = libUI.library.get(originBook);
		if (book.count == 0) {
			return;
		}

		ArrayList<String> borrowers = book.borrowers;

		frame.setPreferredSize(new Dimension(400, 110));
		JLabel nameLabel = new JLabel("姓名");
		nameFiled.setPreferredSize(new Dimension(200, 30));
		panel.setLayout(new FlowLayout());
		panel.add(nameLabel);
		panel.add(nameFiled);

		Container cp = frame.getContentPane();
		cp.add(panel, BorderLayout.CENTER);

		panel = new JPanel(new FlowLayout());
		JButton returnButton = new JButton(borrowFrameAction);
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

	Action borrowFrameAction = new AbstractAction("借书", new ImageIcon("img/borrow.png")) {
		public void actionPerformed(ActionEvent e) {
			book.count--;
			book.borrowers.add(nameFiled.getText());
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