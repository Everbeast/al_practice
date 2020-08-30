//
// Created by ChanChill on 2020-08-30.
//

//用栈实现队列

//https://leetcode-cn.com/problems/implement-queue-using-stacks/
class MyQueue {
    stack<int> st1;
    stack<int> st2;
public:
    /** Initialize your data structure here. */
    MyQueue() {
        while(!st1.empty()) st1.pop();
        while(!st2.empty()) st2.pop();
        st1 = stack<int>();
        st2 = stack<int>();
    }

    /** Push element x to the back of queue. */
    void push(int x) {
        st2.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        peek();
        int ret = st1.top();
        st1.pop();
        return ret;

    }

    /** Get the front element. */
    int peek() {
        if(st1.empty()){
            while(!st2.empty()){
                st1.push(st2.top());
                st2.pop();
            }
        }
        return st1.top();

    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return st1.empty() && st2.empty();

    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */


//用队列实现栈
//https://leetcode-cn.com/problems/implement-stack-using-queues/
class MyStack {
    queue<int> que;
    int top_indx;

public:
    /** Initialize your data structure here. */
    MyStack() {
        que = queue<int>();
        top_indx = -1;
    }

    /** Push element x onto stack. */
    void push(int x) {
        que.push(x);
        top_indx++;
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        while(top_indx > 0){
            que.push(que.front());
            que.pop();
            top_indx--;
        }
        int ret = que.front();
        que.pop();
        top_indx = que.size() - 1;
        return ret;

    }

    /** Get the top element. */
    int top() {
        return que.back();

    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return que.empty();

    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
