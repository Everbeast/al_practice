//
// Created by ChanChill on 2020-09-11.
//

//蓄水池抽样
//以1/i的概率选中第i个数
//https://leetcode-cn.com/problems/linked-list-random-node/
class Solution {
    ListNode* head;
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head):head(head) {}

    /** Returns a random node's value. */
    int getRandom() {
        int i = 2;
        ListNode* cur = head->next;
        int val = head->val;
        while(cur != NULL){
            if(rand() % i == 0) val = cur->val;
            i++;
            cur = cur->next;
        }
        return val;
    }
};

//给定nums 有重复的数，给定target 求随机返回nums中等于target的对应index
//https://leetcode-cn.com/problems/random-pick-index/
class Solution {
    vector<int> nums;
public:
    Solution(vector<int>& nums): nums(nums){}

    int pick(int target) {
        int n = 1;
        int index = 0;
        for(int i = 0; i < nums.size(); i++){
            if(target == nums[i]){
                if(rand() % n == 0) index = i;
                n++;
            }
        }
        return index;
    }
};