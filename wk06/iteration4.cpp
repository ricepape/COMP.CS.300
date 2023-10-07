/**
 * iteration4.cc
 *
 * Print all items of a list in a reverse order
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration4.hh"
using namespace std;


void printReverse(const list<int>& lst)
{
    for (auto it = std::prev(lst.end()); it != lst.begin(); --it)
    {
        std::cout << *it << " ";
    }
    if (!lst.empty()) {
        std::cout << *lst.begin();
    }
    std::cout << std::endl;
}
