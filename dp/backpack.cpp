//
// Created by ChanChill on 2020-07-12.
//
//问题：
//可载重w的背包 n个不同价格，重量的物品，求可装物品的最多价值


//套路
//一
// 1 状态： 背包容量， 可选择物品
// 2 选择： 装入背包 不装入背包
//
// 框架
//for 状态1 in 状态1所有取值:
//    for 状态2 in 状态2所有取值:
//        for ...
//            dp[状态1][状态2][...] = best(选择1, 选择2, ...)

//二
//确定dp数组的意义
//dp[i][w]： 前i个物品，当前背包容量为w时 的最大价值
//套用框架：
//int dp[N+1][W+1]
//dp[0][...] = 0
//dp[...][0] = 0
//for i in [1...N]:
//    for j in [1...W]:
//        dp[i][w] =  max(装i进背包，不装i进背包)
//return dp[N][W]

//三
//根据选择 确定转移方程
//不装i进背包 dp[i][w] = dp[i-1][w]
//装i进背包 dp[i][w] = dp[i-1][w-wt[i-1]] + val[i-1]

// 细化边界条件 完整代码
#include <vector>
using namespace std;

// 0-1 背包
int backpack(int W, int N, vector<int>& wt, vector<int>& val){
    vector<vector<int>> dp(N+1, vector<int>(W+1, 0));
    for(int i = 1; i <= N; i++){
        for(int w = 1; w <= W; w++){
            if(w-wt[i-1] < 0) //超载
                dp[i][w] = dp[i - 1][w];
            else{
                dp[i][w] = max(dp[i - 1][w],
                               dp[i - 1][w - wt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[N][W];
}

//子集背包
//Given a non-empty array containing only positive integers,
// find if the array can be partitioned into two subsets
// such that the sum of elements in both subsets is equal.
//
//链接：https://leetcode-cn.com/problems/partition-equal-subset-sum
// dp[i][j] 表示前i个数能够装满容量为j的背包
bool canPartition(vector<int>& nums) {
    int sum = 0;
    for(auto num : nums) sum += num;
    if(sum %2 != 0) return false; //奇数不能划分两个等分
    sum /= 2;
    int n = nums.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
    //dp[i][j] j=0代表背包装满了
    for(int i = 0; i <= n; i++){
        dp[i][0] = true;
    }
    for(int i = 1; i<= n; i++){
        for(int j = 1; j <= sum; j++){
            //不放入背包
            if(j - nums[i-1] < 0){
                dp[i][j] = dp[i-1][j];
            }
            else{
                //放入或不放入背包
                //注 nums以0开头 故第i的物品时nums[i-1]
                dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
            }
        }
    }
    return dp[n][sum];
}
//压缩空间
bool canPartition_pro(vector<int>& nums) {
    int sum = 0;
    for(auto num : nums) sum += num;
    if(sum %2 != 0) return false; //奇数不能划分两个等分
    sum /= 2;
    int n = nums.size();
    vector<bool> dp(sum + 1, false);
    dp[0] = true;
    for(int i = 0; i < n; i++){
        for(int j = sum; j >= 0; j--){
            if(j - nums[i] >= 0)
                dp[j] = dp[j] || dp[j - nums[i]];
        }
    }
    return dp[sum];
}
//唯一需要注意的是 j 应该从后往前反向遍历，因为每个物品（或者说数字）只能用一次，以免之前的结果影响其他的结果。



//完全背包问题（物品无限量）
//You are given coins of different denominations and a total amount of money.
// Write a function to compute the number of combinations that make up that amount.
// You may assume that you have infinite number of each kind of coin.
//链接：https://leetcode-cn.com/problems/coin-change-2
int change(int amount, vector<int>& coins) {
    int n = coins.size();
    //dp[i][j] 表示前i中硬币凑出总额为j的数目
    vector<vector<int>> dp(n + 1, vector<int>(amount+1, 0));
    for(int i = 0; i <= n; i++){
        dp[i][0] = 1;//总额为0的 什么都不放 因此都至少有一种方法；
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= amount; j++){
            if(j - coins[i-1] >= 0){
                //第i个位置放入  coins以0开始，因此i-1位第i个coins
                dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
            }
            else
                dp[i][j] = dp[i - 1][j]; //i-1个硬币凑出j 第i个位置不放入
        }
    }
    return dp[n][amount];
}

//压缩空间
int change_pro(int amount, vector<int>& coins) {
    int n = coins.size();
    //dp[i][j] 表示前i中硬币凑出总额为j的数目
    vector<int> dp(amount+1, 0);
    dp[0] = 1;//总额为0的 什么都不放 因此都至少有一种方法；
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= amount; j++){
            if(j - coins[i] >= 0)
                dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    return dp[amount];
}