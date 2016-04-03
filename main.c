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

double test(SORT_TYPE *dst, size_t len, SORT_TYPE max, size_t threshold) {
    clock_t t1, t2;

    dst = (SORT_TYPE *) malloc((size_t) sizeof(SORT_TYPE) * len);
    rand_init(dst, max, len);
    merge_sort_threshold = threshold;
    t1 = clock();
    int64_merge_sort(dst, len);
    t2 = clock();

    free(dst);

    return (double) (t2 - t1) / CLOCKS_PER_SEC;
}

int main() {

    SORT_TYPE *dst;
    size_t i, t;
    setlocale(LC_NUMERIC, "");

    const size_t TESTS = 1000;
    const size_t THRESHOLD_TEST = 100;

    for (i = 6; i < TESTS + 2; i++) {
        size_t len = pow(2, i);

        for (t = len / 30; t < len / 10; t+=20) {
//            size_t threshold = (((float) t / THRESHOLD_TEST) * len);
            size_t threshold =  t;
            //threshold = threshold == 1 || threshold == 0 ? 2 : threshold;
            size_t max = 10 * len;
            printf("%d %'20d %'20d %20f \n", i, len, threshold, test(dst, len, max, threshold));
        }
        printf("\n");
    }

    return 0;
}


