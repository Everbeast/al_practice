//
// Created by ChanChill on 2020-09-11.
//
//https://leetcode-cn.com/problems/multiply-strings/
string multiply(string num1, string num2) {
    int n1 = num1.size(), n2 = num2.size();
    vector<int> res(n1 + n2, 0);
    //从个位数相乘
    for(int i = n1 - 1; i >= 0; i--){
        for(int j = n2 - 1; j >= 0; j--){
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j, p2 = i + j +1;
            int sum = mul + res[p2];
            res[p1] += sum / 10;
            res[p2] = sum % 10;
        }
    }
    string ans;
    int i = 0;
    while(i < res.size() && res[i]==0) i++;
    for(;i < res.size(); i++){
        ans += '0' + res[i];
    }
    return ans.size() == 0 ? "0" : ans;
}
