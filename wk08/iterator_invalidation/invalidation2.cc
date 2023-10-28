#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {
    int k = 0;
    for (auto i = vec.begin()+1; i <= vec.end(); i = i+1){ 
        if (k % 2 == 0){
            vec.erase(i);
            }
        k+=1;
        if (i == vec.end()) {
            break; 
        } 
    }
}

