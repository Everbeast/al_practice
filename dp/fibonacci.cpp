//
// Created by ChanChill on 2020-07-01.
//
#include <iostream>
#include <vector>
using namespace std;

//暴力
int fib(int N){
    if(N==1||N==2) return 1;
    return fib(N-1) + fib(N-2);
}

//memo 法
int fib_memo(int N){
    if(N<1) return 0;
    vector<int> memo(N+1, 0);
    return helper(memo, N);
}

int helper(vector<int>& memo, int n){
    if(n==1 || n==2) return 1;
    if(memo[n]!=0) return memo[n];
    memo[n] = helper(memo, n-1) + helper(memo, n-2);
    return memo[n];
}

//dp数组法
int fib_dp(int N){
    vector<int> dp(N+1, 0);
    dp[1]=dp[2]=1;
    for(int i=3;i<=N;i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[N];
}

//dp数组优化空间法
int fib_best(int n){
    if(n==2 || n==1) return 1;
    int prev = 1, curr=1;
    for(int i=3;i<=n;i++){
        int sum = prev + curr;
        prev = curr;
        curr = sum;
    }
    return curr;
}