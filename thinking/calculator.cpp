//
// Created by ChanChill on 2020-09-06.
//
//计算器：s由加减乘除空格组成
//https://leetcode-cn.com/problems/basic-calculator-ii/
int calculate(string s) {
    return helper(s);
}

int helper(string s){
    //存放加减的数
    stack<int> stk;
    int num = 0;
    int sign = '+';

    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        if(isdigit(c)){
            num = num * 10 + (c - '0');
        }
        //遇到不是数字或者到最后 计算i前的数字入栈
        if(!isdigit(c) && c != ' ' || i == s.size() - 1){
            if(sign == '+'){
                stk.push(num);
            }else if(sign == '-'){
                stk.push(-num);
            }else if(sign == '/'){
                //体现乘除法的优先级 先计算 剩下的加减法入栈
                int pre = stk.top();
                stk.pop();
                stk.push(pre / num);
            }else if(sign == '*'){
                //体现乘除法的优先级 先计算 剩下的加减法入栈
                int pre = stk.top();
                stk.pop();
                stk.push(pre * num);
            }
            //num归零  改变符合
            num = 0;
            sign = c;
        }
    }
    int res = 0;
    while(!stk.empty()){
        res += stk.top();
        stk.pop();
    }
    return res;
}


//多了括号的计算器
//利用递归 遇到括号则用递归计算括号的里面的值
//https://leetcode-cn.com/problems/basic-calculator
int calculate(string s) {
    return helper(s);
}
int helper(string& s){
    stack<int> stk;
    int num = 0;
    char sign = '+';


    //利用递归 改变遍历方式 没递归一次 pop 字符串s的首字母
    while(s.size() > 0){
        char c = s[0];
        s = s.substr(1, s.size() - 1);
        if(isdigit(c)){
            num = num * 10 + (c - '0');
        }
        //遇到左括号 递归
        if(c == '('){
            num = helper(s);
        }

        if((!isdigit(c) && c != ' ') || s.size() == 0){
            if(sign == '+'){
                stk.push(num);
            }
            else if(sign == '-'){
                stk.push(-num);
            }
            num = 0;
            sign = c;
        }
        //遇到右括号 结束
        if(c == ')'){
            break;
        }
    }

    int res = 0;
    while(!stk.empty()){
        res += stk.top();
        stk.pop();
    }
    return res;
}