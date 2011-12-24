class Min {
	public static void main(String[] args) {
		int[] arr = {5, 4, 3, 2, 1, 2, 3, 4, 5};
		System.out.println(min(arr, 0));
	}

	static int min(int[] arr, int idx) {
		int len = arr.length - idx;

		if (len == 1) {
			return arr[idx];
		} else if (len == 2) {
			return arr[idx] < arr[idx + 1] ? arr[idx] : arr[idx + 1];
		} else {
			int m = min(arr, idx + 1);
			return arr[idx] < m ? arr[idx] : m;
		}
	}
}
