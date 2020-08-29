//
// Created by ChanChill on 2020-08-29.
//

//You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2.
// Find all the next greater numbers for nums1's elements in the corresponding places of nums2.
/
//The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2.
// If it does not exist, output -1 for this number.
//

//链接：https://leetcode-cn.com/problems/next-greater-element-i
//example:
//Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
//Output: [-1,3,-1]

//next-greater-element-i
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    map<int, int> num_gnum;//
    int n = nums2.size();
    vector<int> greaterVec(n);
    stack<int> st;
    for(int i = n - 1; i >= 0; i--){
        while(!st.empty() && st.top() <= nums2[i]){
            st.pop();
        }
        num_gnum[nums2[i]] = st.empty() ? -1 : st.top();
        st.push(nums2[i]);
    }
    vector<int> ans;
    for(auto i : nums1){
        ans.push_back(num_gnum[i]);
    }
    return ans;
}


//环形单调栈
//https://leetcode-cn.com/problems/next-greater-element-ii/
//InPut: [1,2,1]
//Output: [2,-1,2]
vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    stack<int> st;
    for(int i = 2 * n - 1; i >= 0; i--){
        while(!st.empty() && st.top() <= nums[i % n]){
            st.pop();
        }
        ans[i % n] = st.empty() ? -1 : st.top();
        st.push(nums[i % n]);
    }
    return ans;
}


