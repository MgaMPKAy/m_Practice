
import java.awt.*;
import javax.swing.*;
import java.util.Stack;

public class Calc {
	Stack<Double> operandStack;
	Stack<String> operationStack;
	JTextField numField;
	
	Calc() {
		Stack<Double> operandStack = new Stack<Double>;
		Stack<String> operationStack = new Stack<String>;
		JTextField numField = new JTextField();
	}

	void performOperation(Boolean unary){
		if (unary)
			performUnaryOperation();
		else
			performBinaryOperation();
	}

	void performUnaryOperation() {

	}

	void performBinaryOperation() {

	}

	public static void main(String[] args) {
		JFrame frame = new JFrame("Calc");
		frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);

		JPanel leftPanel = new JPanel();
		leftPanel.setPreferredSize(new Dimension(150, 100));

		String leftPanelOperations = {
			
		}
		
		JPanel centerPanel = new JPanel();
		leftPanel.setPreferredSize(new Dimension(150, 100));
		String leftPanelOperations = {
			
		}
		
		JPanel rightPanel = new JPanel();
		leftPanel.setPreferredSize(new Dimension(150, 100));
		
	}
}

class NumButton extends JButton implements ActionListener {
	private String name;
	private Calc calc;
	NumButton(String name, Calc calc) {
		this.name = name;
		this.calc = calc;
		this.addActionListener(this);
	}

	public void actionPerformed(ActionEvent e) {
		
	}

}

class OperationButton extends JButton implements ActionListener{
	private String name;
	private Calc calc;
	UnaryOperation(String name, Calc calc) {
		this.name = name;
		this.calc = calc;
		this.addActionListener(this);
	}

	public void actionPerformed(ActionEvent e) {
		if (calc.operandStack.isEmpty())
			return;
		if (!calc.operationStack.isEmpty()) {
			calc.performOperation();
			operationStack.push(name);
		}
	}
}