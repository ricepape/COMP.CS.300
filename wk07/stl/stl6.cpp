#include <iterator>
#include <map>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief From a map find the first element, whose value is at least given limit
 *        regardless of the key of the element. Return only the value or
 *        NOT_FOUND if none of the values match the the search criteria.
 * @param m map that is scanned trough
 * @param given limit for the values to search
 * @return int the real found value
 */
int findAtLeastGiven(std::map<std::string, int>& m, int given)
{
    auto it = std::find_if(m.begin(), m.end(), [given](const std::pair<std::string, int>& element) {
        return element.second >= given;
    });

    if (it != m.end() && it->second >= given) {
        return it->second;
    } else {
        return NOT_FOUND;
    }
}


