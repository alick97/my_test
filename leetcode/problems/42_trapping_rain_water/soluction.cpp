#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
       int left = 0, right = height.size() - 1;
       int ans = 0;
       int left_max = 0, right_max = 0;
       while (left < right) {
           if (height[left] < height[right]) {
               height[left] >= left_max ? (left_max = height[left]) : ans += (left_max - height[left]);
               ++left;
           } else {
               height[right] >= right_max ? (right_max = height[right]) : ans += (right_max - height[right]);
               --right;
           }
       } 
       return ans;
    }
};

void test() {
    Solution s;
    // Input: [0,1,0,2,1,0,1,3,2,1,2,1]
    // Output: 6
    vector<int> height_v{0,1,0,2,1,0,1,3,2,1,2,1};
    assert(6 == s.trap(height_v));
}

int main() {
    test();
    return 0;
}
