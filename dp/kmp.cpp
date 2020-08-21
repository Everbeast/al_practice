//
// Created by ChanChill on 2020-08-21.
//
//在haystack中找到匹配子字符床needle 返回匹配的开始索引 无法匹配返回-1
//看labuladong
int strStr(string haystack, string needle) {
    int n = haystack.size();
    int m = needle.size();
    if(m == 0) return 0;
    vector<vector<int>> dp(m, vector<int>(256, 0));
    dp[0][needle[0]] = 1; //转到下一状态（pat的第一个字和自己身的第一个字必定相同 故为1）

    int x = 0;
    for(int j = 1; j < m; j++){
        for(int c = 0; c < 256; c++){
            dp[j][c] = dp[x][c];
        }
        dp[j][needle[j]] = j + 1;

        x = dp[x][needle[j]];
    }

    //search
    int j = 0;
    for(int i = 0; i < n; i++){
        j = dp[j][haystack[i]];
        if(j == m){
            return i - m + 1;
        }
    }
    return -1;

}