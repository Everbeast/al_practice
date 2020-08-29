//
// Created by ChanChill on 2020-08-29.
//
#include <unordered_map>
#include <list>
using namespace std;



//https://leetcode-cn.com/problems/lru-cache/
//自定义双链表==================
struct DLinkedNode{
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr){}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr){}
};

//头为最近使用的
class LRUCache {
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int capacity;
    int size;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0){
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if(cache.find(key) == cache.end())
            return -1;
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;

    }

    void put(int key, int value) {
        if(cache.find(key) != cache.end()){
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
        else{
            if(size >= capacity){
                DLinkedNode* removed = removeTail();
                cache.erase(removed->key);
                delete removed;
                size--;
            }
            size++;
            DLinkedNode* node = new DLinkedNode(key, value);
            cache[key] = node;
            addToHead(node);
        }
    }

    void removeNode(DLinkedNode* node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node){
        removeNode(node);
        addToHead(node);
    }

    void addToHead(DLinkedNode* node){
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    DLinkedNode* removeTail(){
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


//用list=========================================================

struct Node{
    int key, value;
    Node(int _key, int _value):key(_key), value(_value){}
};

class LRUCache {
    unordered_map<int, list<Node>::iterator> mp;
    list<Node> cache;
    int capacity;
public:
    LRUCache(int _capacity):capacity(_capacity){
        cache.clear();
        mp.clear();
    }

    int get(int key) {
        auto it = mp.find(key);
        if(it == mp.end()){
            return -1;
        }
        auto cache_it = it->second;
        int val = cache_it->value;
        cache.erase(cache_it);
        cache.push_front(Node(key, val));
        mp[key] = cache.begin();
        return val;
    }

    void put(int key, int value) {
        auto it = mp.find(key);
        if(it != mp.end()){
            auto cache_it = it->second;
            cache.erase(cache_it);
        }
        else{
            if(capacity <= mp.size()){
                mp.erase(cache.back().key);
                cache.pop_back();
            }
        }
        cache.push_front(Node(key, value));
        mp[key] = cache.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */