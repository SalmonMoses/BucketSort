#include <iostream>
#include <chrono>
#include "arr_utils.h"
#include "utils.h"

#define SIZE 10000u
#define ITERATIONS 100
#define MIN -50
#define MAX 50
typedef std::chrono::microseconds TIME;

using namespace std;

void do_method(
        const char *name,
        void (*sort)(int*, size_t, int, int),
        int *arr,
        const size_t size,
        int min,
        int max,
        TIME::rep copy_delta
) {
    int *work_arr = new int [size];
    __try{
            cout << name << " sort ";
            auto begin = std::chrono::steady_clock::now();
            for (int i = 0; i < ITERATIONS; ++i) {
                cout << ".";
                copy_array(arr, work_arr, SIZE);
                sort(work_arr, SIZE, min, max);
                // print_array(arr, 10);
            }
            auto end = std::chrono::steady_clock::now();
            cout << endl << name << " sort. Average: "
            << (std::chrono::duration_cast<TIME>(end - begin).count() - copy_delta) / ITERATIONS << " ms"
            << endl;
    } __finally {
        delete[] work_arr;
    }
}

int main() {
    int arr[SIZE];
    int sample_arr[SIZE];
    gen_array(sample_arr, SIZE, MIN, MAX);
    auto begin = std::chrono::steady_clock::now();
    cout << "Sample copy ";
    for(int i = 0; i < ITERATIONS; ++i) {
        cout << ".";
        copy_array(sample_arr, arr, SIZE);
    }
    auto end = std::chrono::steady_clock::now();
    TIME::rep copy_time = std::chrono::duration_cast<TIME>(end - begin).count();
    cout << endl << "Copy time: " << copy_time << " ms" << endl;
    do_method("Bubble", bubble_sort, sample_arr, SIZE, MIN, MAX, copy_time);
    do_method("Selection", selection_sort, sample_arr, SIZE, -MIN, MAX, copy_time);
    do_method("Insertion", insert_sort, sample_arr, SIZE, MIN, MAX, copy_time);
    do_method("std::qsort", std_qsort, sample_arr, SIZE, MIN, MAX, copy_time);
    do_method("Bucket", bucket_sort, sample_arr, SIZE, MIN, MAX, copy_time);
    do_method("Parallel bucket", bucket_sort_par, sample_arr, SIZE, MIN, MAX, copy_time);
    return 0;
}
