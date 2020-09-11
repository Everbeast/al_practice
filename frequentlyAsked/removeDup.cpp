//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/
int removeDuplicates(vector<int>& nums) {
    if(nums.empty()) return 0;
    int fast = 0, slow = 0;
    while(fast < nums.size()){
        if(nums[fast] != nums[slow]){
            slow++;
            nums[slow] = nums[fast];
        }
        fast++;
    }
    return slow + 1;
}


//删除链表中重复的
//1
ListNode* deleteDuplicates(ListNode* head) {
    if(head == NULL) return head;
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast != NULL){
        if(fast->val != slow->val){
            slow = slow->next;
            slow->val = fast->val;
        }
        fast = fast->next;
    }
    slow->next = NULL;
    return head;
}

//2
ListNode* deleteDuplicates(ListNode* head){
    ListNode* current = head;
    while(current != nullptr){
        if(current->next != nullptr && current->val == current->next->val)
            current->next = current->next->next;
        else
            current = current->next;
    }
    return head;
}

