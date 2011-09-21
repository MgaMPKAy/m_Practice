class Try {
	public static Boolean fun() {
		try {
			return false;
		} finally {
			return true;
		}
	}

	public static void main(String[] args) {
		System.out.println(fun());
	}
}