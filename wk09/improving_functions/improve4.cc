#include <iterator>
#include <vector>
#include <algorithm>
#include <random>


//---- Some utilities
using iter = std::vector<int>::iterator;
using RNG = std::default_random_engine;

/**
 * @brief Sorts a given vector using a 3 part randomized quicksort algorithm.
 *        Randomization is used to avoid worst case (where the pivot value is
 *        chosen poorly).
 *
 * HINT: The way randomization is implemented can be changed. Shuffle may not
 *       be the only or the best way to implement randomization.
 *
 * @param begin an iterator that points to the beginning part of the sequence where the quicksort is performed.
 * @param end an iterator that points to the end part of the sequence where the quicksort is performed
 * @param rng the random number generator that can be used
 */
void randomizedThreePartQuicksort(iter begin, iter end, RNG& rng)
{
     std::uniform_int_distribution<int> dist(std::distance(begin, end) - 1);
        iter pivot_it = begin + dist(rng);
        int pivot = *pivot_it;

        iter left = begin;
        iter right = end - 1;

        while (left <= right) {
            while (*left < pivot) {
                ++left;
            }
            while (*right > pivot) {
                --right;
            }
            if (left <= right) {
                std::iter_swap(left, right);
                ++left;
                --right;
            }
        }
        iter middle1 = left;
        iter middle2 = left;

        while (middle2 <= end - 1 && *middle2 == pivot) {
            ++middle2;
        }
        
        randomizedThreePartQuicksort(begin, right + 1, rng);   
        randomizedThreePartQuicksort(middle2, end, rng);        

        if (pivot != *middle1) {
            randomizedThreePartQuicksort(middle1, middle2, rng); // Sort elements equal to pivot
        }

        begin = middle2;
}
