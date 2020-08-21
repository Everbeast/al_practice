//
// Created by ChanChill on 2020-08-21.
//


//dp[i][k][s]
//  天数 交易次数 是否持有股票   值为钱
//dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
//                      不买不卖。     卖了
//dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
//.                     不卖不买      买了。（买算一次操作）

//base case
//dp[0][k][0] = 0
//dp[0][k][1] = -infinity
//dp[i][0][0] = 0
//dp[i][0][1] = -infinity

//目标：dp[i][1][0]

//https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/submissions/
//只能交易一次
int maxProfit(vector<int>& prices) {
    // dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][1][1] + prices[i]);
    // dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i]);

    // //base case
    // dp[0][1][0] = 0
    // dp[0][1][1] = -infinity
    // dp[i][0][0] = 0
    // dp[i][0][1] = -infinity

    //综上->
    // dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][1][1] + prices[i]);
    // dp[i][1][1] = max(dp[i-1][1][1], 0 - prices[i]);
    //得全部交易次数都为1 可一消除
    int n = prices.size();
    if(n == 0) return 0;
    vector<vector<int>>dp(n, vector<int>(2, 0));
    for(int i = 0; i < n; i++){
        if(i - 1 == -1){
            //dp[i][0] = max(dp[-1][0]=0, dp[-1][1] = -infinity)
            dp[i][0] = 0;
            //dp[i][1] = max(dp[-1][1]=-infinity, - prices[i])
            dp[i][1] = -prices[i];
        }
        else{
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i-1][1], - prices[i]);
        }
    }
    return dp[n - 1][0];
}

//观察 状态与只与相邻的有关， 可压缩空间
int maxProfit(vector<int>& prices){
    int n = prices.size();
    if(n == 0) return 0;
    int dp_0, dp_1;
    for(int i = 0; i < n; i++){
        if(i - 1 == -1){
            dp_0 = 0;
            dp_1 = -prices[i];
        }
        else{
            dp_0 = max(dp_0, dp_1 + prices[i]);
            dp_1 = max(dp_1, -prices[i]);
        }
    }
    return dp_0;
}



//https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/submissions/
//k = inf

//dp[i][k][0] = max( dp[i-1][k][0], dp[i-1][k][1] + prices[i]); 不动，卖出
//dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);  不动 买入

//base case
// dp[i][0][0] = 0
// dp[i][0][1] = -inf
// dp[0][1][0] = 0
// dp[0][1][1] = -inf


//此题k=inf 故上述k都一样 可以消除
//dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]); 不动，卖出
//dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);  不动 买入

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if(n == 0) return 0;

    vector<vector<int>> dp(n, vector<int>(2, 0));
    int dp_0, dp_1;
    for(int i = 0; i < n; i++){
        if(i - 1 == -1){
            dp[i][0] = 0;
            dp[i][1] = -prices[i];
        }
        else{
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
        }
    }
    return dp[n-1][0];
}

//压缩空间
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if(n == 0) return 0;

    // vector<vector<int>> dp(n, vector<int>(2, 0));
    int dp_0 = 0, dp_1 = -prices[0];
    for(int i = 1; i < n; i++){
        int tmp = dp_0;
        dp_0 = max(dp_0, dp_1 + prices[i]);
        dp_1 = max(dp_1, tmp - prices[i]);

    }
    return dp_0;
}

//https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
//buy and sell with cooltime

//其他同上， 状态转移
////dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]); 不动，卖出
////dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i]);  不动 买入 //买入前一天要cooldown

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if(n == 0) return 0;

    vector<vector<int>> dp(n, vector<int>(2, 0));
    int dp_pre = 0;
    for(int i = 0; i < n; i++){
        if(i - 1 == -1){
            dp[i][0] = 0;
            dp[i][1] = -prices[i];
        }
        else{
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            dp[i][1] = max(dp[i-1][1], dp_pre- prices[i]);
            dp_pre = dp[i-1][0];
        }
    }
    return dp[n-1][0];
}

//压缩空间
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if(n == 0) return 0;

    int dp_0 = 0, dp_1 = -prices[0];
    int dp_pre = 0;
    for(int i = 1; i < n; i++){
        int tmp = dp_0;
        dp_0 = max(dp_0, dp_1 + prices[i]);
        dp_1 = max(dp_1, dp_pre - prices[i]);
        dp_pre = tmp;

    }
    return dp_0;
}


//https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
//sell with fee
int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    if(n == 0) return 0;

    vector<vector<int>> dp(n, vector<int>(2, 0));
    int dp_0, dp_1;
    for(int i = 0; i < n; i++){
        if(i - 1 == -1){
            dp[i][0] = 0;
            dp[i][1] = -prices[i];
        }
        else{
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
        }
    }
    return dp[n-1][0];
}

//压缩空间
int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    if(n == 0) return 0;

    // vector<vector<int>> dp(n, vector<int>(2, 0));
    int dp_0 = 0, dp_1 = -prices[0];
    for(int i = 1; i < n; i++){
        int tmp = dp_0;
        dp_0 = max(dp_0, dp_1 + prices[i] - fee);
        dp_1 = max(dp_1, tmp - prices[i]);

    }
    return dp_0;
}


//https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/
// k = 2

//dp[i][k][0] = max( dp[i-1][k][0], dp[i-1][k][1] + prices[i]); 不动，卖出
//dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);  不动 买入

//base case
// dp[i][0][0] = 0
// dp[i][0][1] = -inf
// dp[0][1][0] = 0
// dp[0][1][1] = -inf

//此处k = 2
//dp[i][2][0] = max( dp[i-1][2][0], dp[i-1][2][1] + prices[i]); 不动，卖出
//dp[i][2][1] = max(dp[i-1][2][1], dp[i-1][1][0] - prices[i]);  不动 买入

//dp[i][1][0] = max( dp[i-1][1][0], dp[i-1][1][1] + prices[i]); 不动，卖出
//dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i]);  不动 买入

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if(n == 0) return 0;

    int dp_i11 = INT_MIN, dp_i21 = INT_MIN;
    int dp_i10 = 0, dp_i20 = 0;
    for(int i = 0; i < n; i++)
    {   //注意顺序
        dp_i20 = max(dp_i20, dp_i21 + prices[i]);
        dp_i21 = max(dp_i21, dp_i10 - prices[i]);
        dp_i10 = max(dp_i10, dp_i11 + prices[i]);
        dp_i11 = max(dp_i11, -prices[i]);
    }
    return dp_i20;
}



//https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/submissions/
//k = 指定次数

//买卖各占一天，故当k/2>天数 就等于 k=inf的情况，调用之前的代码即可

//其他情况 加个遍历 k的循环

int k_inf_maxProfit(vector<int>& prices) {
    int n = prices.size();
    if(n == 0) return 0;

    // vector<vector<int>> dp(n, vector<int>(2, 0));
    int dp_0 = 0, dp_1 = -prices[0];
    for(int i = 1; i < n; i++){
        int tmp = dp_0;
        dp_0 = max(dp_0, dp_1 + prices[i]);
        dp_1 = max(dp_1, tmp - prices[i]);

    }
    return dp_0;
}

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    if(n == 0) return 0;
    if(k / 2 > n)
        return k_inf_maxProfit(prices);

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2, 0)));
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= k; j++){
            if(i - 1 == -1){
                dp[i][j][0] = 0;
                dp[i][j][1] = -prices[i];
            }
            else{
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]); //卖出
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j-1][0] - prices[i]); //买入;
            }
        }
    }
    return dp[n-1][k][0];
}


