//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/valid-parentheses/
bool isValid(string s) {
    stack<char> left;
    for(char c : s){
        if(c == '(' || c == '{' || c == '['){
            left.push(c);
        }else{
            if(!left.empty() && leftof(c) == left.top())
                left.pop();
            else
                return false;
        }
    }
    return left.empty();
}

char leftof(char c){
    if(c == ')') return '(';
    if(c == ']') return '[';
    return '{';
}

