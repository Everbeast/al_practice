//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/reverse-nodes-in-k-group/
ListNode* reverseKGroup(ListNode* head, int k) {
    if(head == NULL) return head;
    ListNode* b = head;
    for(int i = 0; i < k; i++){
        if(b == NULL) return head;
        b = b->next;
    }
    ListNode* a = head;
    ListNode* newHead = reverse(a, b);
    a->next = reverseKGroup(b, k);
    return newHead;
}

ListNode* reverse(ListNode* a, ListNode* b){
    ListNode* pre = NULL;
    ListNode* cur = a;
    while(cur != b){
        ListNode* tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    return pre;
}