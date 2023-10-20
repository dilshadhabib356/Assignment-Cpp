/*

Q3. Write a function that divides an array into chunks such that the sum of each
chunk is <= n. Start from the left side of the array and move to the right.
Examples
divide([1, 2, 3, 4, 1, 0, 2, 2], 5)
➞ [[1, 2], [3], [4, 1, 0], [2, 2]]
divide([1, 0, 1, 1, -1, 0, 0], 1)
➞ [[1, 0], [1], [1, -1, 0, 0]]
divide([2, 1, 0, -1, 0, 0, 2, 1, 3], 3)
➞ [[2, 1, 0, -1, 0, 0], [2, 1], [3]]
Notes
The max of the array will always be smaller than or equal to n.


*/




#include <iostream>
#include <vector>

class ArrayDivider {
public:
    // Method to divide the array based on the given threshold
    std::vector<std::vector<int>> divide(const std::vector<int>& arr, int threshold) const {
        std::vector<std::vector<int>> result;
        std::vector<int> currentChunk;
        int currentSum = 0;

        for (int num : arr) {
            if (currentSum + num > threshold) {
                result.push_back(currentChunk);
                currentChunk.clear();
                currentSum = 0;
            }
            currentChunk.push_back(num);
            currentSum += num;
        }

        if (!currentChunk.empty()) {
            result.push_back(currentChunk);
        }

        return result;
    }
};

int main() {
    ArrayDivider divider;  

    // Test cases
    std::vector<std::vector<int>> testArrays = {
        {1, 2, 3, 4, 1, 0, 2, 2},
        {1, 0, 1, 1, -1, 0, 0},
        {2, 1, 0, -1, 0, 0, 2, 1, 3}
    };
    std::vector<int> thresholds = { 2, 1, 3 };

    for (size_t i = 0; i < testArrays.size(); ++i) {
        auto result = divider.divide(testArrays[i], thresholds[i]);
        for (const auto& chunk : result) {
            std::cout << "[ ";
            for (int val : chunk) {
                std::cout << val << " ";
            }
            std::cout << "] ";
        }
        std::cout << std::endl;
    }

    return 0;
}
