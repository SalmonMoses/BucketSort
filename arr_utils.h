//
// Created by misha on 18.09.2019.
//

#ifndef PANCAKESORT_ARR_UTILS_H
#define PANCAKESORT_ARR_UTILS_H

void copy_array(int *src, int *dst, size_t size);

void selection_sort(int *array, size_t size, int min, int max);

void bubble_sort(int *array, size_t size, int min, int max);

void insert_sort(int *array, size_t size, int min, int max);

void bucket_sort(int *arr, size_t size, int min, int max);

void bucket_sort_par(int *arr, size_t size, int min, int max);

void std_qsort(int *arr, size_t size, int min, int max);

void print_array(int *arr, size_t size);

void gen_array(int *arr, size_t size, int min, int max);

#endif //PANCAKESORT_ARR_UTILS_H
