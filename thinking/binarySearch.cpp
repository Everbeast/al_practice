//
// Created by ChanChill on 2020-09-05.
//

//二分查找法
//https://leetcode-cn.com/problems/binary-search/
int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(nums[mid] == target) return mid;
        else if(nums[mid] < target){
            left = mid + 1;
        }else if(nums[mid] > target){
            right = mid - 1;
        }
    }
    return -1;
}

//查找某数的范围
//https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/
class Solution {
public:
    int left_bound(vector<int>& nums, int target) {
        if (nums.size() == 0) return -1;
        int left = 0;
        int right = nums.size() - 1; // 注意

        while (left <= right) { // 注意
            int mid = left + (right - left) / 2;
            if(nums[mid] == target){
                right = mid - 1;
            }else if(nums[mid] > target){
                right = mid - 1;
            }else if(nums[mid] < target){
                left = mid + 1;
            }
        }
        if(left >= nums.size() || nums[left] != target) return -1;
        return left;
    }

    int right_bound(vector<int>& nums, int target){
        if(nums.size() == 0) return -1;
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target){
                left = mid + 1;
            }else if(nums[mid] > target){
                right = mid - 1;
            }else if(nums[mid] < target){
                left = mid + 1;
            }
        }
        if(right < 0 || nums[right] != target) return -1;
        return right;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ret;
        ret.push_back(left_bound(nums, target));
        ret.push_back(right_bound(nums, target));
        return ret;
    }
};