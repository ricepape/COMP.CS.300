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
    if (begin == end) return;

    std::uniform_int_distribution<size_t> dist(0, std::distance(begin, end) - 1);
    iter pivot = begin + dist(rng);

    auto pivot_value = *pivot;

    iter low = begin;
    iter high = end - 1;
    iter i = begin;

    while (i <= high) {
        if (*i < pivot_value) {
            std::iter_swap(i, low);
            ++low;
            ++i;
        } else if (*i > pivot_value) {
            std::iter_swap(i, high);
            --high;
        } else {
            ++i;
        }
    }

    randomizedThreePartQuicksort(begin, low, rng);
    randomizedThreePartQuicksort(high + 1, end, rng);
}

