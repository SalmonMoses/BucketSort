//
// Created by misha on 18.09.2019.
//

#include <ctime>
#include <iostream>
#include <thread>
#include "arr_utils.h"

#define BUCKET_N 100

using namespace std;

void copy_array(int *src, int *dst, size_t size) {
    for (size_t i = 0; i < size; ++i) *dst++ = *src++;
}

void gen_array(int *arr, size_t size, int min, int max) {
    srand(time(0L));
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % (max - min) + min;
    }
}

void print_array(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insert_sort(int *array, size_t size, int min, int max) {
    for (size_t i = 1; i < size; ++i) {
        int x = array[i];
        int j = i - 1;
        while (j >= 0 && x < array[j]) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = x;
    }
}

void bubble_sort(int *array, size_t size, int min, int max) {
    bool flag = true;
    while (flag) {
        flag = false;
        for (size_t i = 0; i < size - 1; ++i) {
            if (array[i + 1] < array[i]) {
                int tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                flag = true;
            }
        }
    }
}

void selection_sort(int *array, size_t size, int min, int max) {
    for (size_t i = 0; i < size - 1; ++i) {
        int nmin = i;
        int min = array[i];
        for (size_t j = i + 1; j < size; ++j) {
            if (array[j] < min) {
                min = array[j];
                nmin = j;
            }
        }
        array[nmin] = array[i];
        array[i] = min;
    }
}

void bucket_sort(int *arr, size_t size, int min, int max) {
    int *buckets = new int[BUCKET_N * size];
    int *bucket_ptr;
    int **bucket_ends = new int*[BUCKET_N];
    bucket_ptr = buckets;
    for (size_t i = 0; i < BUCKET_N; ++i, bucket_ptr += size) {
        bucket_ends[i] = bucket_ptr;
    }
    const int range = max - min;
    int *arr_ptr = arr;
    for (size_t i = 0; i < size; ++i, ++arr_ptr) {
        int bucket = (*arr_ptr - min) * BUCKET_N / range;
        *bucket_ends[bucket]++ = *arr_ptr;
    }
    bucket_ptr = buckets;
    for (size_t i = 0; i < BUCKET_N; ++i, bucket_ptr += size) {
        int bucket_width = bucket_ends[i] - bucket_ptr;
        if (bucket_width) {
            insert_sort(bucket_ptr, bucket_width, min, max);
        }
    }
    bucket_ptr = buckets;
    arr_ptr = arr;
    for (size_t i = 0; i < BUCKET_N; ++i, bucket_ptr += size) {
        int *bucket_end = bucket_ends[i];
        for (int *ptr = bucket_ptr; ptr != bucket_end;) {
            *arr_ptr++ = *ptr++;
        }
    }
    delete[] bucket_ends;
    delete[] buckets;
}

void bucket_sort_par(int *arr, size_t size, int min, int max) {
    int **buckets = new int *[BUCKET_N];
    size_t *bucket_ends = new size_t[BUCKET_N];
    for (size_t i = 0; i < BUCKET_N; ++i) {
        buckets[i] = new int[size];
        bucket_ends[i] = 0;
    }
    // Sort by buckets
    const int range = max - min;
    for (size_t i = 0; i < size; ++i) {
        int bucket = (arr[i] - min) * BUCKET_N / range;
        buckets[bucket][bucket_ends[bucket]++] = arr[i];
    }
    // debug output
//    for (int i = 0; i < size; ++i) {
    // cout << "Bucket " << i + 1 << ": ", print_array(buckets[i], bucket_ends[i]);
//    }
    // Sort every bucket
    thread *threads = new thread[BUCKET_N];
    size_t thread_n = 0;
//    auto sort_fn = [](const int *arr, size_t size) {
//        qsort((void*) arr, size, sizeof(int), [](void const *a, void const *b) -> int {
//            return *((int const *) a) - *((int const *) b);
//        });
//    };
    for (size_t i = 0; i < BUCKET_N; ++i) {
        if (bucket_ends[i] > 0) {
//            threads[thread_n++] = thread(sort_fn, &(buckets[i][0]), bucket_ends[i]);
            threads[thread_n++] = thread(insert_sort, &(buckets[i][0]), bucket_ends[i], 0, 0);
        }
        // cout << "Bucket " << i + 1 << ": ", print_array(buckets[i], bucket_ends[i]);
    }
    for (size_t i = 0; i < thread_n; ++i) {
        threads[i].join();
    }
    delete[] threads;
    // Merge arrays
    for (size_t i = 0, n = 0; i < BUCKET_N; ++i) {
        for (size_t j = 0; j < bucket_ends[i]; ++j) {
            arr[n++] = buckets[i][j];
        }
    }
    delete[] bucket_ends;
    for (size_t i = 0; i < BUCKET_N; ++i) {
        delete[] buckets[i];
    }
    delete[] buckets;
}

void std_qsort(int *arr, size_t size, int min, int max) {
    qsort(arr, size, sizeof(int), [](void const *a, void const *b) -> int {
        return *((int const *) a) - *((int const *) b);
    });
}
