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
int backpack(int W, int N, vector<int>& wt, vector<int>& val){
    vector<vector<int>> dp(N+1, vector<int>(W+1, 0));
    for(int i=1; i<=N; i++){
        for(int w=1; w<=W; w++){
            if(w-wt[i-1]<0) //超载
                dp[i][w] = dp[i-1][w];
            else{
                dp[i][w] = max(dp[i-1][w],
                               dp[i-1][w-wt[i-1]]+val[i-1]);
            }
        }
    }
    return dp[N][W];
}