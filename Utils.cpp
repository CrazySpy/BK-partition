//
// Created by 蒋希文 on 2021/12/27.
//

#include <vector>
#include <algorithm>
#include "Types.h"

template<typename T>
bool isIntersected(const std::vector<T> &set1, const std::vector<T> &set2) {
    auto it1 = set1.cbegin(), it2 = set2.cbegin();
    while(it1 != set1.end() && it2 != set2.end()) {
        if(*it1 == *it2) {
            return true;
        } else if(*it1 < *it2) {
            ++it1;
        } else {
            ++it2;
        }
    }

    return false;
}

template<typename T>
void orderedInsert(std::vector<T> &set, const T &element) {
    auto it = std::lower_bound(set.begin(), set.end(), element);

    // The element in the set should be unique.
    if(std::binary_search(set.begin(), set.end(), element)) return;

    set.insert(it, element);
}

template<typename T>
std::vector<T> orderedMerge(const std::vector<T> &set1, const std::vector<T> &set2) {
    std::vector<T> result;
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
                   std::back_inserter(result));

    return result;
}

template bool isIntersected<VertexType>(const std::vector<VertexType> &set1, const std::vector<VertexType> &set2);
template void orderedInsert(std::vector<VertexType> &set, const VertexType &element);
template std::vector<VertexType> orderedMerge(const std::vector<VertexType> &set1, const std::vector<VertexType> &set2);