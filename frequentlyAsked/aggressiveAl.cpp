//
// Created by ChanChill on 2020-09-11.
//
//跳跃游戏
//https://leetcode-cn.com/problems/jump-game/
bool canJump(vector<int>& nums) {
    int farthest = 0;
    for(int i = 0; i < nums.size(); i++){
        if(farthest < i) return false;
        farthest = max(farthest, nums[i] + i);
    }
    return true;
}


//跳跃游戏2
//https://leetcode-cn.com/problems/jump-game-ii/

int jump(vector<int>& nums) {
    int farthest = 0;
    int n = nums.size();
    int end = 0;
    int jumps = 0;
    for(int i = 0; i < n - 1; i++){
        farthest = max(farthest, i + nums[i]);
        if(end == i){
            jumps++;
            end = farthest;
        }
    }
    return jumps;
}