import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.JApplet;
import java.util.ArrayList;

public class Calc extends JApplet {
	// 文本框
	protected JTextField numField;
	// 数字按钮，NumButton是JButton子类，Calc内部类
	private NumButton[] numButtons;
	// 运算按钮，OperationButton是JButton子类，Calc内部类
	protected ArrayList<OperationButton> opButtons;
	// 前一个输入
	protected double preInput;
	// 前一个运算，运算按钮使用Operation类
	protected Operation preOp;

	protected State state = State.NoInput;

	// 在够造函数里建GUI， 只使用了FlowLayout，把个元件设置大小后依次放入
	public Calc() {
		super();
		Container contentPane = getContentPane();

		contentPane.setLayout(new FlowLayout());
		setPreferredSize(new Dimension(400, 320));

		createOperationButtons();
		createNumButtons();

		numField = new JTextField();
		numField.setPreferredSize(new Dimension(380, 30));

		add(numField);
		for (NumButton numButton : numButtons) {
			numButton.setPreferredSize(new Dimension(120, 30));
			add(numButton);
		}

		for (OperationButton opButton : opButtons) {
			opButton.setPreferredSize(new Dimension(120, 30));
			add(opButton);
		}

		setVisible(true);
	}

	// 建数字按钮
	private void createNumButtons() {
		numButtons = new NumButton[10];
		for (int i = 0; i <= 9; i++) {
			numButtons[i] = new NumButton(i);
		}
	}

	// 建运算按钮
	private void createOperationButtons() {
		opButtons = new ArrayList<OperationButton>(10);

		// 加法按钮， 使用匿名的Operation
		opButtons.add(new OperationButton("+", new BinaryOperation(this) {
				public double eval() {
					return  preInput + getInput();
				}
			}));

		// substract
		opButtons.add(new OperationButton("-", new BinaryOperation(this) {
				public double eval() {
					return  preInput - getInput();
				}
			}));

		// mult
		opButtons.add(new OperationButton("*", new BinaryOperation(this) {
				public double eval() {
					return  preInput * getInput();
				}
			}));


		// div
		opButtons.add(new OperationButton("/", new BinaryOperation(this) {
				public double eval() {
					return  preInput / getInput();
				}
			}));

		// point
		opButtons.add(new OperationButton(".", new UnaryOperation(this) {
				public void onOneInput(){
					numField.setText(numField.getText() + ".");
				}
				public void onTwoInput(){
					numField.setText(numField.getText() + ".");
				}
				double eval() {
					return getInput();
				}
			}));

		opButtons.add(new OperationButton("^2", new UnaryOperation(this) {
				public double eval() {
					return getInput() * getInput();
				}
			}));


		// sin
		opButtons.add(new OperationButton("sin", new UnaryOperation(this) {
				public double eval() {
					return java.lang.Math.sin(getInput());
				}
			}));

		// cos
		opButtons.add(new OperationButton("cos", new UnaryOperation(this) {
				public double eval() {
					return java.lang.Math.cos(getInput());
				}
			}));

		// tan
		opButtons.add(new OperationButton("tan", new UnaryOperation(this) {
				public double eval() {
					return java.lang.Math.tan(getInput());
				}
			}));

		// 等号，执行前一个运算
		opButtons.add(new OperationButton("=", new UnaryOperation(this) {
				public void performedOP() {
					double result = 0;
					if (preOp != null) {
						result = preOp.eval();
						numField.setText(result + "");
					}
					preInput = result;
					state = State.OneInput;
				}
				public double eval() {
					return getInput();
				}
			}));


		// unsigned / singed
		opButtons.add(new OperationButton("+/-", new UnaryOperation(this) {
				boolean isSign;

				public void performedOP() {
					String input = numField.getText();
					isSign = input.length() > 0 && input.substring(0,1).equals("-");

					if (isSign) {
						numField.setText(input.substring(1, input.length()));
					} else {
						numField.setText("-" + numField.getText());
					}
				}
				public double eval() {
					return getInput();
				}
			}));

		// clear,清空操作，重置状态
		opButtons.add(new OperationButton("Clear", new UnaryOperation(this) {
				public void performedOP() {
					numField.setText("");
					preInput = 0;
					preOp = null;
					state = State.NoInput;
				}
				public double eval() {
					return getInput();
				}
			}));
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
		}
	}

	// 数字按钮
	private class NumButton extends JButton implements ActionListener {
		private String name;
		NumButton(int i) {
			super();
			this.name = i + "";
			this.setText(name);
			this.addActionListener(this);
		}

		public void actionPerformed(ActionEvent e) {
			switch (state) {
			case NoInput:
				numField.setText(numField.getText() + name);
				state = State.OneInput;
				break;
			case OneInput:
				numField.setText(numField.getText() + name);
				break;
			case OneInputOP:
				numField.setText(name);
				state = State.TwoInput;
				break;
			case TwoInput:
				numField.setText(numField.getText() + name);
				break;
			}
			debug();
		}
	}

	// 辅助方法，从输入框获得数字
	public double getInput() {
		double result;
		try {
			result = java.lang.Double.parseDouble(numField.getText());
		} catch (Exception e) {
			numField.setText("Error, please clear input");
			result = 0;
		}
		return result;
	}

	// 调试用，输出各种状态
	private void debug() {
		System.out.println("preInput: " + preInput);
		System.out.println("currentInout:" + numField.getText());
		System.out.println("State: " + state);
		System.out.println("");
	}

	// 毫无特色的主函数
	public static void main(String[] args) {
		new Calc();
	}
}


// Operation类
// 每个运算按钮都使用Operation类，把按钮的表现和操作逻辑的实现分开
abstract class Operation {
	Calc calc;

	Operation(Calc calc) {
		this.calc = calc;
	}

	// Do nothing by deafult
	public void onNoInput() {}

	public void onOneInput() {}

	public void onOneInputOP() {}

	public void onTwoInput() {}


	// 执行各种逻辑判断、GUI和状态更新
	public void performedOP() {
		switch (calc.state) {
		case NoInput:
			onNoInput();
			break;
		case OneInput:
			onOneInput();
			break;
		case OneInputOP:
			onOneInputOP();
			break;
		case TwoInput:
			onTwoInput();
			break;
		}
	}

	// 计算数值结果
	abstract double eval();
}

abstract class UnaryOperation extends Operation {

	UnaryOperation(Calc calc) {
		super(calc);
	}

	public void onOneInput(){
		double input = calc.getInput();
		calc.numField.setText(eval() + "");
	}

	public void onTwoInput(){
		calc.numField.setText(eval() + "");
	}
}

abstract class BinaryOperation extends Operation {

	BinaryOperation(Calc calc) {
		super(calc);
	}

	public void onOneInput(){
		calc.preOp = this;
		calc.preInput = calc.getInput();
		calc.state = State.OneInputOP;
	}

	public void onOneInputOP(){
		calc.preOp = this;
	}

	public void onTwoInput(){
		calc.numField.setText(calc.preOp.eval() + "");
		calc.preInput = calc.getInput();
		calc.preOp = this;
		calc.state = State.OneInputOP;
	}
}

enum State {
		NoInput, OneInput, OneInputOP, TwoInput;
}
