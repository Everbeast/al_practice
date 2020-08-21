//
// Created by ChanChill on 2020-08-15.
//

// Longest Common Subsequence
//Given two strings text1 and text2, return the length of their longest common subsequence.
//
//A subsequence of a string is a new string generated from the original string
// with some characters(can be none) deleted without changing the relative order of the remaining characters.
// (eg, "ace" is a subsequence of "abcde" while "aec" is not). A common subsequence of two strings i
// s a subsequence that is common to both strings
//

//链接：https://leetcode-cn.com/problems/longest-common-subsequence

int longestCommonSubsequence(string text1, string text2) {
    //dp[i][j] 为text1的第i个字母前 和 text2的第j个字母前的最长子序列
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(text1[i - 1] == text2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];

}
//压缩空间
int longestCommonSubsequence(string text1, string text2) {
    //dp[i][j] 为text1的第i个字母前 和 text2的第j个字母前的最长子序列
    int n = text1.size();
    int m = text2.size();
    // vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<int> dp(m + 1, 0);
    for(int i = 1; i <= n; i++){
        int pre = 0;
        for(int j = 1; j <= m; j++){
            int temp = dp[j];
            if(text1[i - 1] == text2[j - 1]){
                // dp[i][j] = dp[i - 1][j - 1] + 1;
                dp[j] = pre + 1;
            }
            else{
                // dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                dp[j] = max(dp[j], dp[j - 1]);
            }
            pre = temp;
        }
    }
    return dp[m];
}
