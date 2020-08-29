//
// Created by ChanChill on 2020-08-29.
//


//https://leetcode-cn.com/problems/lfu-cache/
struct Node{
    int val, key, freq;
    Node(int _val, int _key, int _freq):val(_val), key(_key), freq(_freq){}

};

class LFUCache {
    unordered_map<int, list<Node>::iterator> key_table;
    unordered_map<int, list<Node>> freq_table;
    int capacity;
    int minFreq;
public:
    LFUCache(int _capacity):capacity(_capacity), minFreq(0){
        key_table.clear();
        freq_table.clear();
    }

    int get(int key) {
        if(capacity == 0) return -1;
        auto it = key_table.find(key);
        if(it == key_table.end())
            return -1;
        auto node = it->second;
        int val = node->val, freq = node->freq;
        freq_table[freq].erase(node);
        if(freq_table[freq].size() == 0){
            freq_table.erase(freq);
            if(freq == minFreq) minFreq++;
        }
        freq_table[freq+1].push_front(Node(val, key, freq+1));
        key_table[key] = freq_table[freq+1].begin();
        return val;
    }

    void put(int key, int value) {
        if(capacity == 0) return;
        auto it = key_table.find(key);
        if(it == key_table.end()){ //添加
            if(capacity <= key_table.size()){
                auto node = freq_table[minFreq].back();
                key_table.erase(node.key);
                freq_table[minFreq].pop_back();
            }
            freq_table[1].push_front(Node(value, key, 1));
            key_table[key] = freq_table[1].begin();
            minFreq = 1;

        }
        else{//更新value和freq
            auto node = it->second;
            int freq = node->freq;
            freq_table[freq].erase(node);
            if(freq_table[freq].size() == 0){
                freq_table.erase(freq);
                if(freq == minFreq) minFreq++;
            }
            freq_table[freq+1].push_front(Node(value, key, freq + 1));
            key_table[key] = freq_table[freq+1].begin();

        }

    }

};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */