//
// Created by ChanChill on 2020-09-05.
//
//计算一个数的二进制中有多少个1
//https://leetcode-cn.com/problems/number-of-1-bits/

//利用一个数 n &(n-1) 可以消除 n的二进制数的中的最后一个1
//为0了代表没有1了
int hammingWeight(uint32_t n) {
    int res = 0;
    while(n != 0){
        n = n&(n - 1);
        res++;
    }
    return res;
}

//判断一个数是否为2的冥
//2的幂在二进制中为左移  2^1 = 10   2^2 = 100 ....
//因此二进制数只有一个1则符合条件
//https://leetcode-cn.com/problems/power-of-two/
bool isPowerOfTwo(int n) {
    if(n <= 0 ) return false;
    return (n & (n - 1)) == 0;
}



//在链表中寻找只出现一次的数字（重复的数字只会出现两次）
//https://leetcode-cn.com/problems/single-number/
//一个数和它本身做异或运算结果为 0，即 a ^ a = 0；
//一个数和 0 做异或运算的结果为它本身，即 a ^ 0 = a
int singleNumber(vector<int>& nums) {
    int res = 0;
    for(auto num : nums){
        res ^= num;
    }
    return res;
}

