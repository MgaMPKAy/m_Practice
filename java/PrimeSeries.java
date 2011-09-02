public class PrimeSeries {
	int lowerBound;
	int upperBound;

	public PrimeSeries(int ln, int un) {
		lowerBound = ln;
		upperBound = un;
	}

	public void getPrimeSerise() {
		System.out.println("From " + lowerBound + " to " + upperBound);
		int m = lowerBound;
		while (m <= upperBound) {
			if (m <= 1) {
				++m;
				continue;
			}
			if (isPrime(m)) {
				System.out.print(m + " ");
			}
			++m;
		}
		return;
	}

	static boolean isPrime(int num) {
		for (byte m = 2;  m < num; ++m) {
			if (num % m == 0) {
				return false;
			}
		}
		return true;
	}

	public static void main(String args[]) {
		PrimeSeries ps = new PrimeSeries(2, 20);
		ps.getPrimeSerise();
	}
}