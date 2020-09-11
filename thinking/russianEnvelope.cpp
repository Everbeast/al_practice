//
// Created by ChanChill on 2020-09-11.
//
//给定信封的大小 信封套娃
//https://leetcode-cn.com/problems/russian-doll-envelopes/
int maxEnvelopes(vector<vector<int>>& envelopes) {
    sort(envelopes.begin(),envelopes.end(),[](const vector<int>& a,const vector<int>& b){
        return a[0]<b[0]||(a[0]==b[0]&&a[1]>b[1]);});

    vector<int> height;
    for(int i = 0; i < envelopes.size(); i++){
        height.push_back(envelopes[i][1]);
    }

    return lenghtOfLIS(height);
}

int lenghtOfLIS(vector<int>& height){
    vector<int> dp(height.size(), 1);
    for(int i = 0; i < height.size(); i++){
        for(int j = 0; j < i; j++){
            if(height[i] > height[j]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int res = 0;
    for(int i = 0; i < dp.size(); i++){
        res = max(res, dp[i]);
    }
    return res;
}