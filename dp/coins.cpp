//
// Created by ChanChill on 2020-07-12.
//
//
// 有k种面值硬币，分别c1,c2,...,ck，每种硬币数量无限，再给一个目标总金额amount
// 问：最少需要几枚硬币能凑出目标金额，否则返回-1
//
// 状态：amount
// dp函数定义： 当前金额为n，至少需要dp(n)个硬币凑出amount
// 选择：选择同一种硬币，目amount相应=amount-ck
// 明确base case： amount=0时，需要0个硬币，amount<0时，返回-1


#include <vector>
#include <map>
#include <iostream>

using namespace std;

int coinChange(vector<int>& coins, int amount)
{
    if(amount == 0) return 0;
    if(amount<0) return -1;
    int res = INT8_MIN;
    for(auto coin : coins){
        int subproblem = coinChange(coins, amount-coin);
        if(subproblem == -1) continue;
        res = min(res, 1+subproblem);
    }
    return res==INT8_MIN?-1:res;
}

//memo
int coinChange_memo(vector<int>& coins, int amount){
    map<int, int> memo;
    if(memo.find(amount)!=memo.end())
        return memo[amount];
    if(amount==0) return 0;
    if(amount<0) return -1;
    int res = INT8_MIN;
    for(auto coin : coins){
        int subproblem = coinChange_memo(coins, amount-coin);
        if(subproblem==-1) continue;
        res = min(res, 1+subproblem);
    }
    memo[amount] = res==INT8_MIN?-1:res;
    return memo[amount];
}

//dp数组
//dp[i] = x 表示 目标金额为i时，最少需要x枚硬币

int coinChange_dp(vector<int>& coins, int amount){
    vector<int> dp(amount+1, amount+1);
    dp[0] = 0;
    for(int i=0;i<amount+1;i++){
        for(auto coin : coins){
            if(i-coin < 0) continue;
            dp[i] = min(dp[i], 1+dp[i-coin]);
        }
    }
    dp[amount] = dp[amount] == amount+1?-1:dp[amount];
    return dp[amount];
}