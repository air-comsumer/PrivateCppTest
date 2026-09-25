#include<iostream>
using namespace std;
template<class T>
class ListNode
{
public:
    T val;
    int key;
    ListNode<T>* pre;
    ListNode<T>* next;
    ListNode(int key,const T& data,ListNode<T>* next=nullptr,ListNode<T>* pre=nullptr):key(key),val(data),next(next),pre(pre){}
    ListNode()
    {
        val = T();
        key = 0;
        next = nullptr;
        pre = nullptr;
    }
};