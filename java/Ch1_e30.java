class Ch1_e30 {
	private static void printFibHelper(int n, int a, int b) {
		System.out.print(a + " ");
		if (n != 0) {
			printFibHelper(n - 1, b, a + b);
		}
	}

	public static void printFib(int n) {
		printFibHelper(n, 1, 1);
	}

	public static void main(String[] args) {
		printFib(10);
	}
}