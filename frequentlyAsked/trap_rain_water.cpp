//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/trapping-rain-water/
int trap(vector<int>& height) {
    int n = height.size();
    if(n == 0) return 0;
    int left = 0, right = n - 1;
    int ans = 0;
    int left_max = height[left];
    int right_max = height[right];
    while(left <= right){
        left_max = max(left_max, height[left]);
        right_max = max(right_max, height[right]);

        if(left_max < right_max){
            ans += left_max - height[left];
            left++;
        }else{
            ans += right_max - height[right];
            right--;
        }
    }
    return ans;
}