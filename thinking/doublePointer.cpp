//
// Created by ChanChill on 2020-09-05.
//

//判断链表是否有环
//快慢指针
//https://leetcode-cn.com/problems/linked-list-cycle/
bool hasCycle(ListNode *head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast){
            return true;
        }
    }
    return false;
}



//判断有环的链表环开始的位置
//https://leetcode-cn.com/problems/linked-list-cycle-ii/
ListNode *detectCycle(ListNode *head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast){
            slow = head;
            while(slow != fast){
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return NULL;
}


