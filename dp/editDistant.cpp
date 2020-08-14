//
// Created by ChanChill on 2020-08-14.
//

//Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.
//
//You have the following 3 operations permitted on a word:
//
//Insert a character
//Delete a character
//Replace a character
//
//链接：https://leetcode-cn.com/problems/edit-distance

//Example 1:
//
//Input: word1 = "horse", word2 = "ros"
//Output: 3
//Explanation:
//horse -> rorse (replace 'h' with 'r')
//rorse -> rose (remove 'r')
//rose -> ros (remove 'e')


class Solution {
    string word1;
    string word2;
public:
    int minDistance(string word1, string word2) {
        this->word1 = word1;
        this->word2 = word2;
        return dp(word1.size() - 1, word2.size() - 1);
    }
    int dp(int i, int j){
        if(i == -1) return j + 1;
        if(j == -1) return i + 1;
        if(word1[i] == word2[j]){
            return dp(i - 1, j - 1);
        }
        else{
            return min(dp(i, j - 1) + 1, min(dp(i - 1, j) + 1, dp(i - 1, j -1) + 1));
            //dp(i, j - 1) + 1 word1尾添加
            //dp(i - 1, j) + 1, word1删除
            //dp(i - 1, j - 1) + 1) 替换
        }
    }
};

//真正动态规划方法
int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    //base case
    for(int i = 1; i <= m; i++) dp[i][0] = i;
    for(int j = 1; j <= n; j++) dp[0][j] = j;

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            //第i个字符是从0开始 故 i-1 j-1
            if(word1[i - 1] == word2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1];
            }
            else{
                dp[i][j] = min(dp[i - 1][j] + 1,
                               min(dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1));
            }
        }
    }
    return dp[m][n];
}