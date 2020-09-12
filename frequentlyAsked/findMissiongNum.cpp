//
// Created by ChanChill on 2020-09-11.
//

//找到不见的所有数字
//https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/
vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();
    for(int i = 0; i < n; i++){
        //将该i位置上的数字所指的位置上的数字置为负值  （已经是负则不管）（索引是从0开始 故要-1）
        nums[abs(nums[i]) - 1] = - abs(nums[abs(nums[i]) - 1]);

    }
    vector<int> res;
    for(int i = 0; i < n; i ++){
        //将不是负的数子的索引添加到结果（索引是从0开始 故要+1）
        if(nums[i] > 0) res.push_back(i + 1);
    }
    return res;
}

//同样的方法 寻找一个重复的数字 和 一个missing 的数字
//https://leetcode-cn.com/problems/set-mismatch/
vector<int> findErrorNums(vector<int>& nums) {
    vector<int> res;
    for(int i = 0; i < nums.size(); i++){
        int index = abs(nums[i]) - 1;
        if(nums[index] < 0){
            res.push_back(abs(nums[i]));
        }
        else{
            nums[index] *= -1;
        }

    }
    for(int i = 0; i < nums.size(); i++){
        if(nums[i] > 0){
            res.push_back(i + 1);
        }
    }
    return res;
}

//给定nums 找到 1 - num.size 之间 没有出现的数字
//利用 异或的性质： 和0异或为本身，相同数字异或=0；故和索引异或得到的结果即为不见的数字
int missingNumber(vector<int> nums){
    int n = nums.size();
    int res = n; //因为是找1 - num.size()之间的数字,故要加上n
    for(int i = 0; i < n; i++){
        res  = res ^ i ^ nums[i];
    }
    return res;
}


//用等差数列求和
int missingNumber2(vector<int> nums){
    int n = nums.size();
    // 公式：(首项 + 末项) * 项数 / 2
    int expect = (0 + n) * (n + 1) / 2;

    int sum = 0;
    for(int n : nums){
        sum += n;
    }
    return expect - sum;
}

//直接将数字减去索引
int missingNumer3(vector<int> nums){
    int n = nums.size();
    int res = n; //补充最后一个数字
    for(int i = 0; i < n; i++){
        res = res + i - nums[i];
    }
    return res;
}


