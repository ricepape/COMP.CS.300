#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


bool descending(int a, int b) {
    return a > b;
}

/**
 * @brief sort a given vector to an descending order
 *
 * @param v a vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortDesc(std::vector<int>& v)
{
    std::sort(v.begin(), v.end(), descending);
    return EXIT_SUCCESS;
}

