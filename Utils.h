//
// Created by 蒋希文 on 2021/12/27.
//

#ifndef BK_PARTITION_UTILS_H
#define BK_PARTITION_UTILS_H

#include <vector>
#include "Types.h"

template<typename T>
bool isIntersected(const std::vector<T> &set1, const std::vector<T> &set2);

template<typename T>
void orderedInsert(std::vector<T> &set, const T &element);

template<typename T>
std::vector<T> orderedMerge(const std::vector<T> &set1, const std::vector<T> &set2);

#endif //BK_PARTITION_UTILS_H
