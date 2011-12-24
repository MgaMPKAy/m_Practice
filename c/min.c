#include <stdio.h>

int min(int arr[], int len)
{
	if (len == 1) {
		return arr[0];
	} else if (len == 2) {
		return arr[0] < arr[1] ? arr[0] : arr[1];
	} else {
		int m = min(arr + 1, len - 1);
		return arr[0] < m ? arr[0] : m;
	}
}

int main(int argc, char *argv[])
{
	int arr[] = {5, 4, 3, 2, 1, 2, 3, 4, 5};
	int len = sizeof(arr) / sizeof(int);
	printf("%d\n", min(arr, len));
	
	return 0;
}

