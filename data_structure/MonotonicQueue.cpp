//
// Created by ChanChill on 2020-08-29.
//

//Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
//Output: [3,3,5,5,6,7]
//Explanation:
//
//Window position                Max
//---------------               -----
//[1  3  -1] -3  5  3  6  7       3
// 1 [3  -1  -3] 5  3  6  7       3
// 1  3 [-1  -3  5] 3  6  7       5
// 1  3  -1 [-3  5  3] 6  7       5
// 1  3  -1  -3 [5  3  6] 7       6
// 1  3  -1  -3  5 [3  6  7]      7
//

//链接：https://leetcode-cn.com/problems/sliding-window-maximum


class MonotonicQueue{
private:
    deque<int> data;
public:
    void push(int n){
        while(!data.empty() && data.back() < n){
            data.pop_back();
        }
        data.push_back(n);
    }

    void pop(int n){
        if(!data.empty() && data.front() == n)
            data.pop_front();
    }

    int max(){
        return data.front();
    }
};


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MonotonicQueue window;
        vector<int> ans;
        for(int i = 0; i < nums.size(); i++){
            if(i < k - 1){ //填满窗口前k-1
                window.push(nums[i]);
            }
            else{ //窗口向前滑动
                window.push(nums[i]);
                ans.push_back(window.max());
                window.pop(nums[i - k + 1]); //减去最先进入winodw的元素 （此处window是单调队列，因此不能直接减去window的最前元素
            }
        }
        return ans;
    }
};
