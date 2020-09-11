//
// Created by ChanChill on 2020-09-06.
//
//https://leetcode-cn.com/problems/pancake-sorting/
//Input: arr = [3,2,4,1]
//Output: [4,2,4,3]
//Explanation:
//We perform 4 pancake flips, with k values 4, 2, 4, and 3.
//Starting state: arr = [3, 2, 4, 1]
//After 1st flip (k = 4): arr = [1, 4, 2, 3]
//After 2nd flip (k = 2): arr = [4, 1, 2, 3]
//After 3rd flip (k = 4): arr = [3, 2, 1, 4]
//After 4th flip (k = 3): arr = [1, 2, 3, 4], which is sorted.

vector<int> res;
vector<int> pancakeSort(vector<int>& arr) {
    int n = arr.size();
    sort(arr, n);
    return res;
}

void sort(vector<int>& arr, int n){
    if(n == 1) return;

    int maxIndex = 0;
    int maxVal = 0;
    for(int i = 0; i < n; i++){
        if(maxVal < arr[i]){
            maxVal = arr[i];
            maxIndex = i;
        }
    }
    reverse(arr.begin(), arr.begin() + maxIndex + 1);
    res.push_back(maxIndex + 1);
    reverse(arr.begin(), arr.begin() + n);
    res.push_back(n);

    sort(arr, n - 1);
}