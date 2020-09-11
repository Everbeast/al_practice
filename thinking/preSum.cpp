//
// Created by ChanChill on 2020-09-11.
//
//Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.
//

//链接：https://leetcode-cn.com/problems/subarray-sum-equals-k


int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> preSum;
    preSum[0] = 1;
    int sum_i = 0;
    int ans = 0;
    for(int i = 0; i < nums.size(); i++){
        sum_i += nums[i];
        int sum_j = sum_i - k;
        if(preSum.count(sum_j)){
            ans += preSum[sum_j];
        }
        preSum[sum_i]++;
    }
    return ans;
}