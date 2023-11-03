#include <iterator>
#include <vector>
#include <map>
#include <algorithm>


/**
 * @brief Sums up the values of the vector cumulatively, storing cumulative sum
 *        of the vector in a map, where the keys are the unique vector items,
 *        and the value is the last cumulative sum when that value was last
 *        encountered. (example: {4, 5, 4, 6} => {{4, 13}, {5, 9}, {6, 19}}).
 *
 * @param vec vector which is used for the sum operation.
 * @return std::map<int, int> sums - the sums of each cumulation stored in
 *         a map as values, vector values used as keys.
 */
std::map<int, int> cumulativeSums(std::vector<int> v) {
    std::map<int,int> sums;
    int* p = v.data();

    for (unsigned int i=0; i<v.size(); ++i) {
        if (sums.empty())
        { sums[v[*(p+i)]] = v[*(p+i)]; }
        else
        { sums[v[*(p+i)]] = sums.at(v[*(p+i-1)]) + v[*(p+i)]; }
    }
    return sums;
}
