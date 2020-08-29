//
// Created by ChanChill on 2020-08-29.
//


//Input: [[1,1],2,[1,1]]
//Output: [1,1,2,1,1]

//https://leetcode-cn.com/problems/flatten-nested-list-iterator/

//时间均衡的栈  //预处理和调用的时间平衡
#include<vector>
using namespace std;

//推测该类的构造
class NestedInt{
private:
    int val;
    vector<NestedInt> nestedList;

public:
    NestedInt(int val){
        this->val = val;
        this->nestedList = null;
    }

    NestedInt(nestedList){
        this->val = null;
        this->nestedList = nestedList;
    }

    bool isInteger(){
        return val != null;
    }

    int getInteger(){
        return this->val;
    }

    vector<NestedInt> getList(){
        return this->nestedList;
    }

};

//原题答案
class NestedIterator {
public:
    stack<NestedInteger> st;
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(auto it = nestedList.rbegin(); it != nestedList.rend(); it++){
            st.push(*it);
        }
    }

    int next() {
        int val = st.top().getInteger();
        st.pop();
        return val;
    }

    bool hasNext() {
        while(!st.empty()){
            auto cur = st.top();
            if(cur.isInteger()) return true;
            st.pop();
            auto tmp = cur.getList();
            for(auto it = tmp.rbegin(); it != tmp.rend(); it++){
                st.push(*it);
            }
        }
        return false;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

