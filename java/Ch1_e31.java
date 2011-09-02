class Ch1_e31 {
	public static int[] sort(int arr[]) {
		int[] sorted = arr.clone();
		int tmp;
		for (int i = 0; i < sorted.length; i++) {
			for (int j = i; j > 0; j--) {
				if (sorted[j - 1] > sorted[j]) {
					tmp = sorted[j];
					sorted[j] = sorted[j - 1];
					sorted[j - 1] = tmp;
				}
			}
		}
		return sorted;
	}

	public static void main(String[] args) {
		int[] a = {20, 10, 50, 40, 30, 70, 60, 80, 90, 100};
		int[] b = sort(a);
		for (int v: b)
			System.out.print(v + " ");
		System.out.print('\n');
	}
}