#pragma once
#include<iostream>
#include<vector>
using namespace std;
struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Tree
{
private:
    void deleteTree(TreeNode* node)
    {
        if(node==nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
public:
    TreeNode* root;
    int size;
    int capacity;
    Tree()
    {
        root = nullptr;
        size=0;
        capacity=10;
    }
    ~Tree()
    {
        deleteTree(root);
    }
    TreeNode* flattenAndGetTail(TreeNode* node)
    {
        if(node==nullptr)
            return nullptr;
        TreeNode* leftTail = flattenAndGetTail(node->left);
        TreeNode* rightTail = flattenAndGetTail(node->right);
        if(leftTail!=nullptr)
        {
            leftTail->right = node->right;
            node->right = node->left;
            node->left = nullptr;
        }
        if(rightTail!=nullptr)
            return rightTail;
        if(leftTail!=nullptr)
            return leftTail;
        return node;
    }
    void flatten(TreeNode* root) 
    {
        flatten(root);
    }
    vector<int> inorderTraversal(TreeNode* root) 
    {
        vector<int> a;
        inorder(root,a);
        return a;
    }
    void inorder(TreeNode* node,vector<int>& a)
    {
        if(node==nullptr)
            return;
        inorder(node->left,a);
        a.push_back(node->val);
        inorder(node->right,a);
    }
    void invert(TreeNode* node)
    {
        if(node==nullptr)
            return;
        invert(node->left);
        invert(node->right);
        TreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
    TreeNode* invertTree(TreeNode* root) 
    {
        invert(root);
        return root;
    }
};
