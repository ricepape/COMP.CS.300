#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)
{
    std::vector<int> mod0, mod1, mod2;

    std::copy_if(v.begin(), v.end(), std::back_inserter(mod0), [](int num) { return num % 3 == 0; });
    std::copy_if(v.begin(), v.end(), std::back_inserter(mod1), [](int num) { return num % 3 == 1; });
    std::copy_if(v.begin(), v.end(), std::back_inserter(mod2), [](int num) { return num % 3 == 2; });

    std::sort(mod0.begin(), mod0.end());
    std::sort(mod1.begin(), mod1.end());
    std::sort(mod2.begin(), mod2.end());

    v.clear();
    v.insert(v.end(), mod0.begin(), mod0.end());
    v.insert(v.end(), mod1.begin(), mod1.end());
    v.insert(v.end(), mod2.begin(), mod2.end());

    return EXIT_SUCCESS;
}

