#include <iterator>
#include <vector>
#include <algorithm>


/**
 * @brief Gets the smallest value from the vector passed as a parameter.
 *
 * @param vec vector which is searched for the smallest value.
 * @return int - the smallest value or 0 (zero) if vector is empty.
 */
int minValue(std::vector<int> vec){
    if ( vec.empty() ) { return 0; }
    int* p = vec.data(); // Get a pointer to the first element of the vector
    int min = 0;
    for (int i = 0; i < size(vec); i++) {
        if (*(p + i) < min){
            min = *(p+i);
        } // Assign values using pointer arithmetic
    }

    return min;
}
