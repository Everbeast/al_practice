//
// Created by ChanChill on 2020-08-20.
//
//Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
//
//'.' Matches any single character.
//'*' Matches zero or more of the preceding element.
//
//链接：https://leetcode-cn.com/problems/regular-expression-matching

//暴力法
bool isMatch(string s, string p) {
    if(!p.size()) return !s.size();

    bool first = s.size() && (s[0] == p[0] || p[0] == '.');

    //暴力迭代
    if(p.size() >= 2 && p[1] == '*'){
        return isMatch(s, p.substr(2)) || (first && isMatch(s.substr(1), p));
    }
    else{
        return first && isMatch(s.substr(1), p.substr(1));
    }
}

//如何发现子问题：
//def dp(n):
//  dp(n - 1) #1
//  dp(n - 2) #2
// dp[n] -> dp[n-2] 有两种方法：1、dp[n]->dp[n-1]->dp[n-2] #1->#1  2、dp[n]->dp[n-2] #2

//memo法
class Solution {
    string s;
    string p;
public:
    bool isMatch(string s, string p) {
        this->s = s;
        this->p = p;
        map<string, int> memo;
        return dp(0, 0, memo);
    }

    bool dp(int i, int j, map<string, int>& memo){
        string key = to_string(i)+','+to_string(j);
        if(memo.find(key) != memo.end())
            return memo[key];

        if(j == p.size()) return i == s.size();
        bool first = i < s.size() && (p[j] == s[i] || p[j] == '.');

        bool ans;
        if(j <= p.size() - 2 && p[j + 1] == '*'){
            ans = dp(i, j + 2, memo) ||(first && dp(i + 1, j, memo));
        }
        else{
            ans = first && dp(i + 1, j + 1, memo);
        }
        memo[key] = ans;
        return ans;
    }
};