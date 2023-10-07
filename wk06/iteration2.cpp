/**
 * iteration2.cc
 *
 * Print every second item of a list starting from the first item
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration2.hh"
using namespace std;


void printEverySecond(const list<int>& lst)
{
    int size = lst.size();

    auto it = lst.begin();
    
    // Iterate until the midpoint
    for (int i = 0; i < size; ++i)
    {
        if (i % 2 == 0){
            std::cout << *it << " ";
        }
        ++it; // Move the iterator to the next element
    }
    
    std::cout << std::endl;
}




