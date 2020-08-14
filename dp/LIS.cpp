//
// Created by ChanChill on 2020-07-12.
//

//Longest increasing subsequence

//步骤：
// 1 先定义dp[i]表示以nums[i]这个数结尾的最长递增序列长度
// 2 确定转移方程：如求dp[5]，设nums[5]=3,则找到前面dp[k] k<3的值 选择dp[5] dp[k]+1的较大者
#include <vector>
using namespace std;

int lenghtOfLIS(vector<int>& nums){
    vector<int> dp(nums.size(),1);
    for(int i = 0;i < nums.size();i++){
        for(int j = 0;j < i;j++){
            if(nums[i] > nums[j])
                dp[i] = max(dp[i], dp[j]+1);
        }
    }
    //遍历dp找出最大值
    int res = 0;
    for(auto &i: dp) res = max(res, i);
    return res;
}

//仅供拓展: 二分查找法 （扑克牌玩法） ：证明略
int LIS_b_search(vector<int>& nums){
    int top[nums.size()]; // 当前堆低的值
    int piles = 0; //堆的长度为lis
    for(int i = 0;i < nums.size();i++){
        int poker = nums[i];

        //搜索左侧边界的二分查找，left表示要插入的堆
        int left = 0, right = piles;
        while(left < right){
            int mid = (left+right) / 2;
            if(top[mid] > poker) right = mid;
            else if (top[mid] < poker) left = mid;
            else right=mid;  //搜索左边界
        }
        if(left == piles) piles++;//没有合适的堆，新建一个堆；
        top[left] = poker;
    }
    return piles;
}