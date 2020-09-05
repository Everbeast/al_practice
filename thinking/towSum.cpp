//
// Created by ChanChill on 2020-09-05.
//


//给定链表 找到两个数的和等于target
//https://leetcode-cn.com/problems/two-sum/

//1 穷举法

//2 用哈希表加速
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> idx;
    for(int i = 0; i < nums.size(); i++){
        idx[nums[i]] = i;
    }

    for(int i = 0; i < nums.size(); i++){
        int other = target - nums[i];
        if(idx.find(other) != idx.end() && idx[other] != i){
            return vector<int>{i, idx[other]};
        }
    }
    return vector<int>();
}

