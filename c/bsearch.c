bsearch(int e, int *arr, int l, int r)
{
	int mid = (l + r) / 2;
	if (l > r) {
		return -1;
	} else if (arr[mid] == e) {
		return mid;
	} else if (arr[mid] > e) {
		return bsearch(e, arr, l, mid - 1);
	} else {
		return bsearch(e, arr, mid + 1, r);
	} 
}

bsearch2(int e, int *arr, int l, int r)
{
	int mid, m;
	
	while (l <= r) {
		mid = (l + r) / 2;
		m = arr[mid];
		if (m == e) {
			return mid;
		} else if (m > e) {
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return -1;
}
