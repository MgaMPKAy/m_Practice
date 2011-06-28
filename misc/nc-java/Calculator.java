class Calculator {
	private int integer1;
	private int integer2;
	private char oprator;
	private static int result = 0;

	static {
		System.out.println("Start :" + result);
	}

	public Calculator(int i1, char op, int i2) {
		integer1 = i1;
		integer2 = i2;
		oprator = op;
	}

	public Calculator(char op, int i2) {
		integer1 = result;
		oprator = oprator;
		integer2 = i2;
	}

	public Calculator(char op) throws UnsupportedOperationException {
		if (op == '=') {
			System.out.println("Result: " + result);
		} else {
			throw new UnsupportedOperationException();
		}
	}

	public int calculate()
		throws ArithmeticException, UnsupportedOperationException {
		if (oprator == '+') {
			result = integer1 + integer2;
		} else if (oprator == '-') {
			result = integer1 - integer2;
		} else if (oprator == '*') {
			result = integer1 * integer2;
		} else if (oprator == '/') {
			if (integer2 == 0) {
				throw new ArithmeticException();
			} else {
				result = integer1 / integer2;
			}
		} else {
			throw new UnsupportedOperationException();
		}
		return result;
	}

	public static void main(String args[]) {
		try {
			Calculator c1 = new Calculator(3, '+' , 2);
			c1.calculate();
			Calculator c2 = new Calculator('*', 6);
			c2.calculate();
			Calculator c3 = new Calculator('-', 20);
			c3.calculate();
			Calculator c4 = new Calculator('/', 5);
			c4.calculate();
			Calculator c5 = new Calculator('=');
			c5.calculate();
		} catch (ArithmeticException ae) {
			System.out.println("Exception" + ae);
		} catch (UnsupportedOperationException ue) {
			System.out.println("Exception" + ue);
		}
	}
}