//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/count-primes
int countPrimes(int n) {
    vector<bool> isPrimes(n, true);
    for(int i = 2; i * i < n; i++){
        for(int j = i * i; j < n; j += i){
            isPrimes[j] = false;
        }
    }
    int count = 0;
    for(int i = 2; i < n; i++){
        if(isPrimes[i]) count++;
    }
    return count;
}