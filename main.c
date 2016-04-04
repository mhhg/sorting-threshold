#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <inttypes.h>
#include <locale.h>

#define SORT_NAME int64
#define SORT_TYPE int64_t
#define SORT_CMP(x, y) ((x) - (y))

#include "sort.h"

#define SORT_TYPE int64_t
#define PRT PRId64

void rand_init(SORT_TYPE *dst, SORT_TYPE max, size_t len) {

	srand(time(NULL)); // start rand
	size_t i;

	for (i = 0; i < len; i++)
		dst[i] = rand() % max;
}

void print(SORT_TYPE *arr, size_t len) {
	//    return;
	int idx;

	for (idx = 0; idx < len; idx++) {
		printf("%" PRT " ", arr[idx]);
	}

	printf("\n");
}

size_t pow(size_t n, size_t p) {
	size_t ret = 1, idx;
	for (idx = 0; idx < p; idx++) {
		ret *= n;
	}
	return ret;
}

double test(void(*func)(SORT_TYPE *, size_t), SORT_TYPE *dst, size_t len, size_t threshold) {
	clock_t t1, t2;

	merge_sort_threshold = threshold;
	t1 = clock();
	func(dst, len);
	t2 = clock();

	return (double)(t2 - t1) / CLOCKS_PER_SEC;
}

int main() {

	SORT_TYPE *dst, *tmp;
	double *time_arr;

	size_t i, t = 2;
	setlocale(LC_NUMERIC, "");

	size_t len = pow(10, 8);
	size_t max = 10 * len;

	dst = (SORT_TYPE *)malloc((size_t) sizeof(SORT_TYPE) * len);
	tmp = (SORT_TYPE *)malloc((size_t) sizeof(SORT_TYPE) * len);

	rand_init(dst, max, len);

	memcpy(tmp, dst, len * sizeof(SORT_TYPE));
	double merge_sort_time = test(int64_merge_sort, tmp, len, 0);


	double min = merge_sort_time;
	size_t min_idx = 0;
	double merge_t = 0;


	//printf("insertion sort: %20d %20d %20f \n", len, t, insertion_sort_time);
	printf("merge sort    : %20d %20d %20f \n", len, t, merge_sort_time);


	for (i = 10; i < 30; i += 1) {
		memcpy(tmp, dst, len * sizeof(SORT_TYPE));
		merge_t = test(int64_merge_sort, tmp, len, i);
		if (merge_t < min) {
			min = merge_t;
			min_idx = i;
			//printf("merge sort t  : %20d %20d %20f \n", len, i, merge_t);
			
		}
		
	}

	printf("best time: %f, index=%d\n", min, min_idx);
	//print(time_arr, time_arr_len);
	free(dst);
	free(tmp);
	getch();
	return 0;
}
