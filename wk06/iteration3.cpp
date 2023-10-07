/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;



void printHalf(const list<int>& lst)
{
    // Calculate the number of elements in the list
    int size = lst.size();

    // Calculate the midpoint (rounded down if size is odd)
    int midpoint = size / 2;

    // Use an iterator to traverse the list
    auto it = lst.begin();
    
    // Iterate until the midpoint
    for (int i = 0; i < midpoint; ++i)
    {
        std::cout << *it << " ";
        ++it; // Move the iterator to the next element
    }
    
    std::cout << std::endl;
}





