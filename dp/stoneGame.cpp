//
// Created by ChanChill on 2020-08-20.
//

//Alex and Lee play a game with piles of stones.  There are an even number of piles arranged in a row,
// and each pile has a positive integer number of stones piles[i].
//
//The objective of the game is to end with the most stones.  The total number of stones is odd, so there are no ties.
//
//Alex and Lee take turns, with Alex starting first. 
// Each turn, a player takes the entire pile of stones from either the beginning or the end of the row. 
// This continues until there are no more piles left, at which point the person with the most stones wins.
//
//Assuming Alex and Lee play optimally, return True if and only if Alex wins the game.
//

//链接：https://leetcode-cn.com/problems/stone-game

bool stoneGame(vector<int>& piles) {
    int n = piles.size();
    vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, make_pair(0,0)));
    //dp[i][j].first 表在ij区间的十块堆中 先手能获得的最高分数
    //dp[i][j].second 表在ij区间的十块堆中 后手手能获得的最高分数
    //目标 求dp[0][n-1]

    //base case
    for(int i = 0; i < n; i++){
        dp[i][i] = make_pair(piles[i], 0);
    }

    //状态转移
    // dp[i][j] = max(左边的， 右边的)
    // dp[i][j].first = max(piles[i] + dp[i+1][j].second, piles[j] + dp[i][j-1])

    //若先手选左边：则后手等于 dp[i][j].sencond = dp[i][j-1].fisrt

    //  [i][j-1]  [i][j]
    //            [i+1][j]
    for(int l = 2; l <= n; l++){
        for(int i = 0; i <= n - l; i++){
            int j = i + l - 1;
            //先手选左
            int left = piles[i] + dp[i + 1][j].second;
            //选右
            int right = piles[j] + dp[i][j - 1].second;
            if(left > right){
                dp[i][j].first = left;
                dp[i][j].second = dp[i + 1][j].first;
            }
            else{
                dp[i][j].first = right;
                dp[i][j].second = dp[i][j - 1].first;
            }
        }
    }

    return dp[0][n - 1].first > dp[0][n - 1].second ? true : false;
}