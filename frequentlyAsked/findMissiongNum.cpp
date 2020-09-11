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