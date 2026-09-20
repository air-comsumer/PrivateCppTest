#include<iostream>
#include<vector>
using namespace std;
class ListNode
{
public:
    int val;
    ListNode* next;
    ListNode()
    {
        val = int();
        next = nullptr;
    }
    ListNode(int a)
    {
        val =a;
        next = nullptr;
    }
    ListNode(int a,ListNode* next):val(a),next(next){}
};
class MyList
{
public:
    ListNode* head;
    MyList(ListNode* node)
    {
        head = node;
    }
    MyList()
    {
        head = new ListNode();
    }
    MyList(const int* a,int n)
    {
        head = new ListNode(a[0]);
        ListNode* p = head;
        for(int i=1;i<n;i++)
        {
            p->next = new ListNode(a[i]);
            p=p->next;
        }
    }
    MyList(const vector<int>& a)
    {
        ListNode* p = head;
        p->val=a[0];
        for(size_t i=1;i<a.size();i++)
        {
            p->next = new ListNode(a[i]);
            p=p->next;
        }
    }
    ~MyList()
    {
        ListNode* temp = head;
        while(temp!=nullptr)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
        delete head;
    }
    void PrintList()
    {
        ListNode* p = head;
        while(p!=nullptr)
        {
            cout<<p->val<<" ";
            p=p->next;
        }
        cout<<endl;
    }
    ListNode* ReverseList1()
    {
        head = ReverseList1(head);
        return head;
    }
    ListNode* ReverseList1(ListNode* node)
    {
        if(node==nullptr|| node->next==nullptr)
            return node;
        ListNode* left=node->next;
        ListNode* right = left->next;
        node->next = nullptr;
        left->next = node;
        while (right!=nullptr)
        {
            node = left;
            left = right;
            right = right->next;
            left->next = node;
        }
        return left;
    }
    ListNode* ReverseList2()
    {//翻转链表递归法
        head = ReverseList2(head);
        return head;
    }
    ListNode* ReverseList2(ListNode* node)
    {
        if(node==nullptr||node->next==nullptr)
            return node;
        ListNode* newNode = ReverseList2(node->next);
        node->next->next = node;
        node->next = nullptr;
        return newNode;
    }
    bool Palindrome(ListNode* head)
    {
        if(head==nullptr||head->next==nullptr)
            return true;
        ListNode* left = head;
        ListNode* right = head;
        while(right->next!=nullptr&&right->next->next!=nullptr)
        {   //这里用right->next->next，是因为如果是两个数的时候，right！=null的判断条件会执行一次
            //这样left的位置就在链表末尾，left->next=nullptr，所以left=nullptr直接跳过第二个循环
            left=left->next;
            right = right->next->next;
        }
        left = ReverseList2(left->next);
        while(left!=nullptr)
        {
            if(left->val!=head->val)
                return false;
            left = left->next;
            head = head->next;
        }
        return true;
    }
    ListNode* frontPointer;
    bool Recursively(ListNode* currentNode)
    {
        if(currentNode!=nullptr)
        {
            if(!Recursively(currentNode->next))
                return false;
            if(currentNode->val!=frontPointer->val)
                return false;
            frontPointer = frontPointer->next;
        }
        return true;
    }
    bool Palindrome2(ListNode* node)
    {
        if(node==nullptr||node->next==nullptr)
            return true;
        frontPointer = node;
        return Recursively(node);       
    }
};

ListNode* InterSectionList(ListNode* a,ListNode* b)
{//相交位置在a+b-c
    ListNode* tempA = a;
    ListNode* tempB = b;
    while(tempA!=tempB)
    {
        tempA = tempA!=nullptr?tempA->next:b;
        tempB = tempB!=nullptr?tempB->next:a;
    }
    return tempA;
}

bool HasCycle(ListNode* head)
{
    if(head==nullptr||head->next==nullptr)
        return false;
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow==fast)
        {
            return true;
        }
    }
    return false;
}
ListNode* MergeTwoList(ListNode* a,ListNode* b)
{
    if(a==nullptr)
        return b;
    if(b==nullptr)
        return a;
    if(a->val<b->val)
    {
        a->next = MergeTwoList(a->next,b);
        return a;
    }
    else
    {
        b->next = MergeTwoList(a,b->next);
        return b;
    }
}
ListNode* SortMergeTowList(ListNode* head1,ListNode* head2)
{
    if(head1==nullptr)
        return head2;
    if(head2==nullptr)
        return head1;
    if(head1->val<head2->val)
    {
        head1->next=SortMergeTowList(head1->next,head2);
        return head1;
    }
    else
    {
        head2->next=SortMergeTowList(head1,head2->next);
        return head2;
    }    
}
ListNode* SortMergeTowList2(ListNode* head1,ListNode* head2)
{
    ListNode dummy(0);
    ListNode* temp = &dummy;
    while(head1!=nullptr&&head2!=nullptr)
    {
        if(head1->val<head2->val)
        {
            temp->next = head1;
            head1 = head1->next;
        }
        else
        {
            temp->next = head2;
            head2 = head2->next;
        }
        temp = temp->next;            
    }
    if(head1==nullptr)
    {
        temp->next=head2;
    }
    else if(head2==nullptr)
    {
        temp->next = head1;
    }
    return dummy.next;
}
ListNode* ListSort(ListNode* head)
{
    if(head==nullptr)
        return head;
    //先获得链表长度
    ListNode* temp = head;
    int length = 0;
    while(temp!=nullptr)
    {
        length++;
        temp = temp->next;
    }
    //设置不断变化的滑动长度
    ListNode dummy(0,head);
    for(int sliderLength=1;sliderLength<length;sliderLength<<=1)
    {//<<=2 = *=2
        ListNode* prev = &dummy;
        ListNode* cur = dummy.next;
        while(cur!=nullptr)//开始滑动遍历
        {
            ListNode* head1 = cur;
            for(int i=1;i<sliderLength&&cur->next!=nullptr;i++)
            {
                    cur=cur->next;
            }
            ListNode* head2 = cur->next;
            cur->next=nullptr;
            cur=head2;//完成第一次滑动，合并左边就是head1
            for(int i=1;i<sliderLength&&cur!=nullptr&&cur->next!=nullptr;i++)
            {//这里cur!=nullptr是为了防止上一步head2本来就是nullptr
                cur=cur->next;
            }
            ListNode* next=nullptr;
            if(cur!=nullptr)
            {//如果出来cur=nullptr这里也会空引用
                next = cur->next;
                cur->next = nullptr;
            }
            ListNode* merge = SortMergeTowList(head1,head2);
            prev->next=merge;
            while(prev->next!=nullptr)
            {
                prev=prev->next;
            }
            cur = next;
        }
    }
    return dummy.next;
}
//递归法 参数应该是链表的头和尾
//返回值应该是排序结束后的链表头
//在函数体里面就是要把划分的链表合并
ListNode* sortList(ListNode* head,ListNode* tail)
{
    if(head==tail)
        return head;
    if(head->next==tail)
    {
        head->next=nullptr;
        return head;
    }
    ListNode* fast=head,*slow= head;
    while(fast!=tail&&fast->next!=tail)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* left=sortList(head,slow);
    ListNode* right = sortList(slow,tail);
    return SortMergeTowList(left,right);
}
ListNode* sortList(ListNode* head)
{
    return sortList(head,nullptr);
}
