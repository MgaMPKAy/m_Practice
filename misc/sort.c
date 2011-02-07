#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define ITEM int
/* TODO:
   对比对同一数组排序用的时间:复制数组
   可以选择排序的方法
   命令行参数调用排序算法
   实现快排（多种）,猴子，抖动，堆排，计数,基数
   提高时间精度
   MAYBE:多文件
*/

void selection(ITEM *, int l ,int r);
void bubble(ITEM arr[], int l ,int r);
void quicksort(ITEM arr[], int l, int r);
void insertion(ITEM arr[], int l, int r);
void shellsort(ITEM arr[], int l, int r);

void merege(ITEM arr[], int l , int mid, int r);
void meregesort(ITEM arr[], int l ,int r);

void output_arr(ITEM arr[], int n);
ITEM *make_random_arr(int n, int max);
void free_arr(ITEM **arr);


int main(int argc, char *argv[])
{
	ITEM *arr1, *arr2;
	int n,max,output = 1;
	time_t start, end;
	int i;
	
	if(argc < 3){
		printf("Enter N MAX:");
		scanf("%i %i", &n, &max);
		if (n <= 0 || max <= 0){
			printf("Usage ...\n");
			exit(EXIT_SUCCESS);
		}
	} else {
		n = atoi(*(argv+1));
		max = atoi(*(argv+2));
		if (argc > 3)
			output = atoi(*(argv+3));
		if (n <= 0 || max <= 0){
			printf("Usage ...\n");
			exit(EXIT_SUCCESS);
		}
	}
	
	srand((unsigned)time(NULL));  
	arr1 = make_random_arr(n, max);
	arr2 = malloc(sizeof(ITEM) * n);
	for (i = 0; i < n; i++)
		arr2[i] = arr[i];
	
	if(output == 1) output_arr(arr1, n);// should be improved
	start = clock(); 
	meregesort(arr, 0, n-1);
	end = clock();
	if(output == 1) output_arr(arr1, n);// should be improved
	printf("Time used: %.2lfms\n",(double)(end-start));
	
	if(output == 1) output_arr(arr2, n);// should be improved
	start = clock(); 
	quicksort(arr2, 0, n-1);
	end = clock();
	if(output == 1) output_arr(arr2, n);// should be improved
	printf("Time used: %.2lfms\n",(double)(end-start));
	
	free_arr(&arr);
	free_arr(&arr2);
		
	return 0;
}


void selection(ITEM arr[], int l ,int r)
{
	int i, j , min;
	ITEM t;
	for(i = l; i < r; i++){
		min = i;
		for(j = i; j <= r; j++)
			if (arr[j] < arr[min])
				min = j;
		t = arr[i];
		arr[i] = arr[min];
		arr[min] = t;
	}
}


void bubble(ITEM arr[], int l ,int r)
{
	int i, j;
	ITEM t;
	for(i = l; i <= r; i++)
		for(j = r; j > l; j--)
			if (arr[j-1] > arr[j]){
				t = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = t;
			}
}


void quicksort(ITEM *arr, int l, int r)
{
	if (l >= r)
		return; 
	int p = rand()%(r - l + 1) + l;
	ITEM pr = arr[p];
	int i = l - 1, j = r + 1;
	ITEM t;
	while(i <= j){
		do {i++;}
		while((arr[i] < pr)&&(i<=r));
		do {j--;}
		while((arr[j] > pr)&&(j>=l));
		
		if (i < j){
			t = arr[i];arr[i] = arr[j]; arr[j] = t;
		}
	}
  	quicksort(arr,l,j);
	quicksort(arr,j+1,r);
}


void insertion(ITEM arr[], int l, int r)
{
	int i, j;
	ITEM t;
	for(i = r; i > l; i--)
		if (arr[i]< arr[i-1])
			{t = arr[i-1]; arr[i-1] = arr[i]; arr[i] = t;}
  
	for(i = l + 2; i <= r; i++){
		t = arr[i];
		j = i - 1;      
		while (j >= 1 && arr[j] > t) {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = t;
	}
}

void shellsort(ITEM *arr ,int l, int r)
{
	
	int step[] = {29524 ,9841 ,3280, 1093 ,364, 121, 40, 13, 4, 1};
	int i, j, k;
	ITEM min, s;
	for (k = 0; k < sizeof(step)/sizeof(step[0]); k++){
		s = step[k];
		for (i = s; i <= r; i++){
			min  = arr[i];
			j = i - s;
			while(j >= 0 && arr[j] > min){
				arr[j+s] = arr[j];
				j -= s;
			}
			arr[j+s] = min;
		}
	}
}

void merege(ITEM *arr, int start , int mid, int end)
{
	int n1 = mid - start + 1;
	int n2 = end - mid;
	int i, j, k;
	/* int left[n1], right[n2];  c99-only? */
	
	ITEM *left = malloc(sizeof(ITEM) * n1);
	ITEM *right = malloc(sizeof(ITEM) * n2);
	if (left == NULL && right == NULL)
		exit(EXIT_SUCCESS);
	
	for (i = 0; i < n1; i++)
		left[i] = arr[start+i];
	for (j = 0; j < n2; j++)
		right[j] = arr[mid + 1 + j];
	i = j = 0;
	k = start;
	
	while(i < n1 && j < n2)
		if (left[i] < right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	while (i < n1)
		arr[k++] =left[i++];
	while (j < n2)
		arr[k++] = right[j++];
	free(left);
	free(right);
}

void meregesort(int *arr, int l, int r)
{
	int mid;
	if (l < r){
		mid = (l + r) / 2;
		meregesort(arr, l, mid);
		meregesort(arr, mid + 1, r);
		merege(arr, l, mid, r);
	}
}
void output_arr(ITEM arr[], int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%3d ",arr[i]);
	printf("\n");
}


ITEM *make_random_arr(int n, int max)
{
	ITEM *arr;
	int i;
	if((arr =malloc(n * sizeof(int)))==NULL)
		{/* errno = 11 */; perror("malloc"); exit(11);}

	for(i = 0; i < n; i++)
		arr[i]= rand()%max+1;
	return arr;
}


void free_arr(ITEM **arr)
{
	free(*arr);
	*arr = NULL;
}
