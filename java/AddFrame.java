import javax.swing.*;
import java.awt.*;

public class AddFrame extends JFrame {
	private JTextField nameField;
	private JTextField authorField;
	private JTextField pressField;
	private JTextField numField;
	private JTextField isbnField;
	       
	AddFrame() {
		super();

		setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
		
		JLabel label = new JLabel("Hello");
		Container contentPane = getContentPane();
		contentPane.add(label);

		pack();
		setVisible(true);
	}
	
}
	