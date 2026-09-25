#include<iostream>
#include"ListNode.hpp"
#include<unordered_map>
using namespace std;
class LRUCache
{
private:
    ListNode<int>* head;
    ListNode<int>* tail;
    unordered_map<int,ListNode<int>*> cache;
    int capacity;
    int size;
    void moveToHead(ListNode<int>* target)
    {
        target->pre->next = target->next;
        target->next->pre = target->pre;
        target->next = head->next;
        target->pre = head;
        head->next->pre = target;
        head->next = target;
    }
    ListNode<int>* removeTail()
    {
        ListNode<int>* deleteNode = tail->pre;
        deleteNode->pre->next = tail;
        tail->pre = deleteNode->pre;
        return deleteNode;
    }
public:
    LRUCache()
    {
        head=new ListNode<int>();
        tail=new ListNode<int>();
        head->next = tail;
        tail->pre = head;
        capacity = 10;
        size=0;
    }
    LRUCache(int capacity)
        : head(new ListNode<int>()),
            tail(new ListNode<int>()),
            capacity(capacity),
            size(0)
    {
    head->next = tail;
    tail->pre = head;
    }
    int get(int key)
    {
        if(!cache.count(key))
        {
            return -1;
        }
        ListNode<int>* node = cache[key];
        moveToHead(node);
        return node->val;
    }

    void put(int key,int value)
    {
        if(!cache.count(key))
        {
            ListNode<int>* node = new ListNode<int>(key,value);
            cache[key] = node;
            node->pre = head;
            node->next= head->next;
            head->next = node;
            node->next->pre = node;
            size++;
            if(size>capacity)
            {
                ListNode<int>* node = removeTail();
                cache.erase(node->key);
                delete node;
                size--;
            }
        }
        else
        {
            ListNode<int>* temp =  cache[key];
            temp->val = value;
            moveToHead(temp);
        }

    }
};


