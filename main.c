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

double test(void (*func)(SORT_TYPE *, size_t), SORT_TYPE *dst, size_t len, size_t threshold) {
    clock_t t1, t2;

    merge_sort_threshold = threshold;
    t1 = clock();
    func(dst, len);
    t2 = clock();

    return (double) (t2 - t1) / CLOCKS_PER_SEC;
}

int main() {

    SORT_TYPE *dst, *tmp_dst;
    size_t i, t = 2;
//    setlocale(LC_NUMERIC, "");

    size_t len = pow(10, 5);
    size_t max = 10 * len;

    dst = (SORT_TYPE *) malloc((size_t) sizeof(SORT_TYPE) * len);
    tmp_dst = (SORT_TYPE *) malloc((size_t) sizeof(SORT_TYPE) * len);

    rand_init(dst, max, len);

    memcpy(tmp_dst, dst, len * sizeof(SORT_TYPE));

    double insertion_sort_time = test(int64_binary_insertion_sort, tmp_dst, len, 0);

    memcpy(tmp_dst, dst, len * sizeof(SORT_TYPE));
    double merge_sort_time = test(int64_merge_sort, tmp_dst, len, 0);

    for(i = 100; i < 400; i+=10){
        memcpy(tmp_dst, dst, len * sizeof(SORT_TYPE));
//        print(tmp_dst, len);
        double merge_sort_with_threshold = test(int64_merge_sort, tmp_dst, len, i);
        printf("merge sort t  : %'20d %'20d %20f \n", len, i, merge_sort_time);

    }

    printf("insertion sort: %20d %20d %20f \n", len, t, insertion_sort_time);
    printf("merge sort    : %20d %20d %20f \n", len, t, merge_sort_time);

    //print(tmp_dst, len);
    printf("\n");
    //print(dst, len);


    free(dst);
    free(tmp_dst);
    return 0;
}


