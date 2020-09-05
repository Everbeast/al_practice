//
// Created by ChanChill on 2020-09-05.
//

///* 滑动窗口算法框架 */
//void slidingWindow(string s, string t) {
//    unordered_map<char, int> need, window;
//    for (char c : t) need[c]++;
//
//    int left = 0, right = 0;
//    int valid = 0;
//    while (right < s.size()) {
//        // c 是将移入窗口的字符
//        char c = s[right];
//        // 右移窗口
//        right++;
//        // 进行窗口内数据的一系列更新
//        ...
//
//        /*** debug 输出的位置 ***/
//        printf("window: [%d, %d)\n", left, right);
//        /********************/
//
//        // 判断左侧窗口是否要收缩
//        while (window needs shrink) {
//            // d 是将移出窗口的字符
//            char d = s[left];
//            // 左移窗口
//            left++;
//            // 进行窗口内数据的一系列更新
//            ...
//        }
//    }
//}

//

//https://leetcode-cn.com/problems/minimum-window-substring/
//examle:
//Input: S = "ADOBECODEBANC", T = "ABC"
//Output: "BANC"
string minWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for(int i = 0; i < t.size(); i++){
        need[t[i]]++;
    }
    int left = 0, right = 0;
    int valid = 0;
    int start = 0, len = INT_MAX;
    while(right < s.size()){
        char c = s[right];
        right++;
        if(need.count(c)){
            window[c]++;
            if(window[c] == need[c]){
                valid++;
            }
        }

        while(valid == need.size()){
            if(right - left < len){
                start = left;
                len = right - left;
            }
            char d = s[left];
            left++;
            if(need.count(d)){
                if(window[d] == need[d]){
                    valid--;
                }
                window[d]--;
            }
        }
    }
    return len == INT_MAX ? "" : s.substr(start, len);
}




//寻找s2中是否有s1的任意顺序的子字符串
//Input: s1 = "ab" s2 = "eidbaooo"
//Output: True

//Input:s1= "ab" s2 = "eidboaoo"
//Output: False
//
//https://leetcode-cn.com/problems/permutation-in-string

bool checkInclusion(string s1, string s2) {
    unordered_map<char, int> need, window;
    for(int i = 0; i < s1.size(); i++){
        need[s1[i]]++;
    }


    int left = 0, right = 0;
    int valid = 0;
    while(right < s2.size()){
        char c = s2[right];
        right++;
        if(need.count(c)){
            window[c]++;
            if(window[c] == need[c]){
                valid++;
            }
        }

        while(right-left >= s1.size()){
            if(valid == need.size()) return true; //注意need.size 不同于 s1.size
            char d = s2[left];
            left++;
            if(need.count(d)){
                if(window[d] == need[d]){
                    valid--;
                }
                window[d]--;
            }
        }
    }
    return false;

}



//查找全部字串的首位置
//https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/
vector<int> findAnagrams(string s, string p) {
    unordered_map<char, int> need, window;
    for(char c : p){
        need[c]++;
    }

    int left = 0, right = 0;
    int valid = 0;
    vector<int> res;
    while(right < s.size()){
        char c = s[right];
        right++;
        if(need.count(c)){
            window[c]++;
            if(window[c] == need[c]){
                valid++;
            }
        }
        while(right - left >= p.size()){
            if(valid == need.size()) res.push_back(left);
            char d = s[left];
            left++;
            if(need.count(d)){
                if(window[d] == need[d]){
                    valid--;
                }
                window[d]--;
            }
        }
    }
    return res;


    //找字符串中最大的不重复的子串的长度
    //https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> window;
        int left = 0, right = 0;
        int res = 0;
        while(right < s.size()){
            char c = s[right];
            right++;
            window[c]++;

            while(window[c] > 1){
                char d = s[left];
                left++;
                window[d]--;
            }
            res = max(res, right-left);

        }
        return res;

    }