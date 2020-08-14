//
// Created by ChanChill on 2020-08-14.
//
#include <iostream>
#include <vector>
using namespace std;

int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;
    vector<int> dp(n);
    dp[0] = nums[0];
    for(int i = 1; i < n; i++){
        dp[i] = max(dp[i-1] + nums[i], nums[i]);
    }
    int res = INT8_MIN;
    for(int i = 0; i < dp.size(); i++){
        res = max(dp[i], res);
    }
    return res;
}

//因为dp[i] 只和 dp[i-1]有关系 因此可以压缩空间

int maxSubArray_pro(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;

    int dp_1, dp_0 = nums[0];
    int res = dp_0;
    for(int i = 1; i < n; i++){
        dp_1 = max(dp_0 + nums[i], nums[i]);
        dp_0 = dp_1;
        res = max(res, dp_1);
    }
    return res;
}