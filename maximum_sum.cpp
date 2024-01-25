#include <iostream>
#include <vector>
#include <climits>

std::vector<int> maxSubArray(const std::vector<int>& nums) {
    int maxSum = INT_MIN, currentSum = 0;
    int start = 0, end = 0, s = 0;

    for (int i = 0; i < nums.size(); i++) {
        currentSum += nums[i];

        if (maxSum < currentSum) {
            maxSum = currentSum;
            start = s;
            end = i;
        }

        if (currentSum < 0) {
            currentSum = 0;
            s = i + 1;
        }
    }

    return std::vector<int>(nums.begin() + start, nums.begin() + end + 1);
}

int main() {
    
    std::vector<int> evenCase = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::vector<int> result = maxSubArray(evenCase);
    std::cout << "Max subarray in even case: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    
    std::vector<int> oddCase = {1, 2, 3, 4, -10, 5, 6};
    result = maxSubArray(oddCase);
    std::cout << "Max subarray in odd case: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
