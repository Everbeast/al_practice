//
// Created by ChanChill on 2020-08-20.
//
//Given a string s, find the longest palindromic subsequence's length in s.
// You may assume that the maximum length of s is 1000.
//
//
//链接：https://leetcode-cn.com/problems/longest-palindromic-subsequence
//

int longestPalindromeSubseq(string s) {
    int n = s.size();
    // dp[i][j]表示在字符串在i到j区间形成的最长回文子串
    //目标是dp[0][n-1]
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        dp[i][i] = 1;
    }
    for(int i = n - 1; i >= 0; i--){
        for(int j = i + 1; j < n; j++){
            if(s[i] == s[j])
                dp[i][j] = 2 + dp[i + 1][j - 1];
            else
                dp[i][j] = max(dp[i][j - 1],
                               dp[i + 1][j]);
        }
    }
    return dp[0][n - 1];
}

