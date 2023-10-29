#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */
void duplicateEvenRemoveUneven(std::vector<int>& vec) {
    using Iter = std::vector<int>::iterator;

    for (Iter it = vec.begin(); it != vec.end(); ) {
    if (*it % 2 == 0) {
        vec.insert(it, *it);  // Duplicate the even number.
        if (it + 2 != vec.end()){
            it += 2;  // Move the iterator 2 positions forward (skip the duplicated element).
        }
    }
    else {
        it = vec.erase(it);  // Remove the odd number and update the iterator.
    }
}
}

