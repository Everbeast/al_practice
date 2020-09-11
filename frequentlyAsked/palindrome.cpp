//
// Created by ChanChill on 2020-09-11.
//
//寻找最长回文子串
string longestPalindrome(string s) {
    string res;
    for(int i = 0; i < s.size(); i++){
        string s1 = Palindrome(s, i, i);
        string s2 = Palindrome(s, i, i + 1);
        res = res.size() > s1.size() ? res : s1;
        res = res.size() > s2.size() ? res : s2;
    }
    return res;
}

string Palindrome(string& s, int l, int r){
    while(l >= 0 && r <s.size() && s[l] == s[r]){
        l--;
        r++;
    }
    return s.substr(l + 1, r - l - 1);
}



//判断链表是否为回文链表
//https://leetcode-cn.com/problems/palindrome-linked-list/
bool isPalindrome(ListNode* head) {
    ListNode* mid = findMid(head);
    ListNode* right = reverse(mid);
    ListNode* recoverHead = right;
    ListNode* left = head;
    while(right != NULL){
        if(left->val != right->val){
            reverse(recoverHead); //恢复链表结构
            return false;
        }
        left = left->next;
        right = right->next;
    }

    reverse(recoverHead); //恢复链表结构
    return true;
}

ListNode* findMid(ListNode* head){
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    if(fast != NULL) slow = slow->next; //代表链表数目为奇数  slow再走一步 指向中间节点的下一个节点
    return slow;
}

ListNode* reverse(ListNode* head){
    ListNode* pre = NULL;
    ListNode* cur = head;
    while(cur != NULL){
        ListNode* tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    return pre;
}

