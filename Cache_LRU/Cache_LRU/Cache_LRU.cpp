/*
 
 146. LRU Cache
 
 https://leetcode.com/problems/lru-cache/description/

 Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.
 
 get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
 
 Follow up:
 Could you do both operations in O(1) time complexity?
 
 Example:
 
 LRUCache cache = new LRUCache( 2  ); // capacity

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
 
 */

#include <iostream>
#include <unordered_map>

using namespace std;



class LRUCache {
private:
    class LinkedList{
    private:
        class Node{
        public:
            int key;
            shared_ptr<Node> prev, next;
            Node(int key) : key{key}, prev{nullptr}, next{nullptr} {}
        };
        shared_ptr<Node> _head, _tail;
        int _size, _cap;
        
    public:
        LinkedList() {
            _head=make_shared<Node>(-1);
            _tail=make_shared<Node>(-1);
            _head->next=_tail;
            _tail->prev=_head;
            _size=0;
            _cap=0;
        }
        
        int Size() { return _size; }
        
        void Cap(int capacity) { _cap=capacity; }
        
        bool Full(){
            return _size>=_cap;
        }
        
        void Add(int key){
            auto node=make_shared<Node>(key);
            node->prev=_head;
            node->next=_head->next;
            _head->next->prev=node;
            _head->next=node;
            ++_size;
        }
        
        void Del(int key){
            shared_ptr<Node> itr=_head->next;
            while (itr!=_tail && itr->key!=key){
                itr=itr->next;
            }
            if (itr!=_tail){
                itr->prev->next=itr->next;
                itr->next->prev=itr->prev;
                --_size;
            }
        }
        
        shared_ptr<Node> Pop(){
            if (Size()==0) return nullptr;
            auto res=_tail->prev;
            _tail->prev->prev->next=_tail;
            _tail->prev=_tail->prev->prev;
            return res;
        }
    };
    
    unordered_map<int,int> _hash{};
    LinkedList _list{};
    
public:
    LRUCache(int capacity){
        _list.Cap(capacity);
    }
    
    int get(int key) {
        auto entry=_hash.find(key);
        if (entry==_hash.end()) return -1;
        int val=entry->second;
        _list.Del(key);
        _list.Add(key);
        return val;
    }
    
    void put(int key, int val) {
        auto entry=_hash.find(key);
        if (entry==_hash.end()){
            if (_list.Full()){
                auto del=_list.Pop();
                _hash.erase(del->key);
            }
        }
        _list.Del(key);
        _list.Add(key);
        _hash[key]=val;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

int main(int argc, const char * argv[]) {

    LRUCache c(2);
    
    c.put(1,1);
    c.put(2,2);
    c.put(3,3);
    cout << c.get(2) << endl;
    
    return 0;
}




