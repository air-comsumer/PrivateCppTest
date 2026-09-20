#include<iostream>
#include<string>
#include"MyList.hpp"
using namespace std;
int main()
{
    int a[] = {5, 2, 4, 1, 3};
    MyList list(a, 5);
    list.head = sortList(list.head);
    list.PrintList();
    cin.ignore();
    cin.get();
    return 0;
}
