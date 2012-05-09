import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Stack;

public class Calc extends JFrame {
	private JTextField numField;
	private NumButton[] numButtons;
	private OperationButton[] opButtons;
	private double preInput;
	private Operation preOp;
	private boolean begin = true;
	private int count;

	Calc() {
		super();

		setLayout(new FlowLayout());
		setPreferredSize(new Dimension(400, 600));
		setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);

		createOperationButtons();
		createNumButtons();

		numField = new JTextField();
		numField.setPreferredSize(new Dimension(380, 30));

		add(numField);
		for (int i = 0; i <= 9; i++) {
			numButtons[i].setPreferredSize(new Dimension(120, 30));
			add(numButtons[i]);
		}

		for (int i = 0; i <= 5; i++) {
			opButtons[i].setPreferredSize(new Dimension(120, 30));
			add(opButtons[i]);
		}

		pack();
		setVisible(true);
	}

	void createNumButtons() {
		numButtons = new NumButton[10];
		for (int i = 0; i <= 9; i++) {
			numButtons[i] = new NumButton(i);
		}
	}

	void createOperationButtons() {
		opButtons = new OperationButton[6];

		opButtons[0] = new OperationButton("+", new Operation() {
				public void performedOP() {
					if (count == 0) {
						if (numField.getText().equals("")) {
							return;
						}
						preInput = getInput();
						preOp = this;
						count = 1;
					} else if (count == 1) {
						preOp = this;
					} else {
						double result = preOp.eval();
						numField.setText(result + "");
						preInput = result;
					preOp = this;
						count = 1;

					}

				}
				public double eval() {
					return  preInput + getInput();
				}
			});

		opButtons[1] = new OperationButton("-", new Operation() {
				public void performedOP() {
					if (begin) {
						numField.setText("-" + numField.getText());
						begin = false;
						return;
					}
					if (count == 0) {
						if (numField.getText().equals("")) {
							return;
						}
						preInput = getInput();
						preOp = this;
						count = 1;
					} else if (count == 1) {
						preOp = this;
					} else {
						double result = preOp.eval();
						numField.setText(result + "");
						preInput = result;
						preOp = this;
						count = 1;
					}
				}

				public double eval() {
					return  preInput - getInput();
				}
			});

		opButtons[2] = new OperationButton("*", new Operation() {
				public void performedOP() {
					if (count == 0) {
						if (numField.getText().equals("")) {
							return;
						}
						preInput = getInput();
						preOp = this;
						count = 1;
					} else if (count == 1) {
						preOp = this;
					} else {
						double result = preOp.eval();
						numField.setText(result + "");
						preInput = result;
						preOp = this;
						count = 1;
					}

				}

				public double eval() {
					return  preInput * getInput();
				}
			});

		opButtons[3] = new OperationButton("/", new Operation() {
				public void performedOP() {
					if (count == 0) {
						if (numField.getText().equals("")) {
							return;
						}
						preInput = getInput();
						preOp = this;
						count = 1;
					} else if (count == 1) {
						preOp = this;
					} else {
						double result = preOp.eval();
						numField.setText(result + "");
						preInput = result;
						preOp = this;
						count = 1;
					}
				}

				public double eval() {
					return  preInput / getInput();
				}
			});

		opButtons[4] = new OperationButton("=", new Operation() {
				public void performedOP() {
					if (count == 0) {
						if (numField.getText().equals("")) {
							return;
						}
						preInput = getInput();
						preOp = this;
						count = 1;
					} else if (count == 1) {
						preOp = this;
					} else {
						if (preOp != null)  {
							preOp.performedOP();
						}
						preOp = this;
					}

				}

				public double eval() {
					return getInput();
				}
			});

		opButtons[5] = new OperationButton("Clear", new Operation() {
				public void performedOP() {
					numField.setText("");
					begin = true;
					preInput = 0;
					count = 0;
					preOp = null;
				}
				public double eval() {
					return getInput();
				}
			});
	}

	private class OperationButton extends JButton implements ActionListener {
		private String name;
		Operation op;
		OperationButton(String name, Operation op){
			super();
			this.name = name;
			this.setText(name);
			this.op = op;
			this.addActionListener(this);
		}

		public void actionPerformed(ActionEvent e) {
			op.performedOP();
			debug();
			begin = true;
		}
	}

	private class NumButton extends JButton implements ActionListener {
		private String name;
		NumButton(int i) {
			super();
			this.name = i + "";
			this.setText(name);
			this.addActionListener(this);
		}

		public void actionPerformed(ActionEvent e) {
			if (preOp != null && count == 1) {
				numField.setText("");
				count = 2;
			}
			if (begin) {
				begin = false;
			}
			numField.setText(numField.getText() + name);
			debug();
		}
	}

	private interface Operation {
		void performedOP();
		double eval();
	}

	private double getInput() {
		double result;
		try {
			result = java.lang.Double.parseDouble(numField.getText());
		} catch (Exception e) {
			numField.setText("Error, please clear input");
			result = 0;
		}
		return result;
	}

	private void debug() {
		System.out.println("count: " + count);
		System.out.println("preInput: " + preInput);
		System.out.println("currentInout:" + numField.getText());
		System.out.println("");
	}

	public static void main(String[] args) {
		new Calc();
	}
}