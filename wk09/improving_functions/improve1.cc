#include <iterator>
#include <vector>
#include <algorithm>


/**
 * @brief creates a vector of integers with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 * @return std::vector<int>
 */
std::vector<int> ascendingVector(int n){
    if (n <= 0) {
        return std::vector<int>(); // Return an empty vector for n <= 0
    }

    std::vector<int> v(n);
    int* p = v.data(); // Get a pointer to the first element of the vector

    for (int i = 0; i < n; i++) {
        *(p + i) = i; // Assign values using pointer arithmetic
    }

    return v;
}
