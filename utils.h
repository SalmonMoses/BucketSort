//
// Created by misha on 20.09.2019.
//

#ifndef PANCAKESORT_UTILS_H
#define PANCAKESORT_UTILS_H

template<typename T>
T sum(T elem[], unsigned int size) {
    long sum = 0;
    for(int i = 0; i < size; sum = sum + elem[i++]);
    return sum;
}

#endif //PANCAKESORT_UTILS_H
