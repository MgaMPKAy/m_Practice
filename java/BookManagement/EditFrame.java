import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;

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
