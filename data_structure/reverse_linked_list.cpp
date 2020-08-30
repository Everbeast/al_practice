//
// Created by ChanChill on 2020-08-30.
//

//https://leetcode-cn.com/problems/reverse-linked-list-ii/


//reverse all linked list
 ListNode* reverse(ListNode* head){
     if(head->next == NULL) return head;
     ListNode* last = reverse(head->next);
     head->next->next = head;
     head->next = NULL;
     return last;
 }



//reverse N node of linked list
ListNode* successor;
ListNode* reverseN(ListNode* head, int n){
    if(n == 1){
        successor = head->next;
        return head;
    }
    ListNode* last = reverseN(head->next, n-1);
    head->next->next = head;
    head->next = successor;
    return last;

}

//reverse n nodes begin at m
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if(m == 1) return reverseN(head, n);
    head->next = reverseBetween(head->next, m - 1, n - 1);
    return head;
}
