//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/super-pow/
int base = 1337;
int myPow(int a, int b){
    int res = 1;
    a = a % base;
    for(int i = 0; i < b; i++){
        res *= a;
        res  = res % base;
    }
    return res;
}

int superPow(int a, vector<int>& b) {
    if(b.empty()) return 1;
    int last = b.back();
    b.pop_back();

    int part1 = myPow(a, last);
    int part2 = myPow(superPow(a, b), 10);
    return (part1 * part2) % base;
}