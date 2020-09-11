//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/shuffle-an-array/
class Solution {
    vector<int> nums;
    vector<int> copy;
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
        this->copy = nums;
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        nums.clear();
        nums.assign(copy.begin(), copy.end());
        return nums;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        for(int i = 0; i < nums.size(); i++){
            int rd = rand() % (i + 1);
            swap(nums[rd], nums[i]);
        }
        return nums;
    }
};



