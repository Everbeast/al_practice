//
// Created by ChanChill on 2020-08-20.
//
//Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums.
// You are asked to burst all the balloons.
// If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.
// Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.
//
//Find the maximum coins you can collect by bursting the balloons wisely.
//

//链接：https://leetcode-cn.com/problems/burst-balloons

int maxCoins(vector<int>& nums) {
    //添加头尾虚拟节点
    int n = nums.size();
    vector<int> points(n+2, 0);
    points[0] = 1;
    points[n + 1] = 1;
    for(int i = 1; i <= n; i++){
        points[i] = nums[i - 1];
    }

    //dp[i][j]表示在ij区间中戳气球所得到的最高分数(开区间，不包括ij)
    //即目标为dp[0][n+1]
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    for(int i = n + 1; i >= 0; i--){
        for(int j = i + 1; j <= n + 1; j++){
            for(int k = i + 1; k < j; k++){
                dp[i][j] = max(dp[i][j],
                               dp[i][k] + dp[k][j] + points[i]*points[k]*points[j]);
            }
        }

    }
    return dp[0][n + 1];
}

