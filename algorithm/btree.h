/**
 * @file btree.h
 * @author yangzs 
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include <functional>
#include <queue>

template <class T>
struct BTreeNode
{
    BTreeNode *left;
    BTreeNode *right;
    T val;
    ~BTreeNode(){
        delete left,right;
    }
};

template <class T>
class BTree
{
public:
    BTree();
    virtual ~BTree();
    virtual void preOrder(BTreeNode<T> *node, std::function<void(BTreeNode<T> *)> visitFunc);
    virtual void inOrder(BTreeNode<T> *node, std::function<void(BTreeNode<T> *)> visitFunc);
    virtual void postOrder(BTreeNode<T> *node, std::function<void(BTreeNode<T> *)> visitFunc);
    virtual void levelOrder(BTreeNode<T> *node, std::function<void(BTreeNode<T> *)> visitFunc);
    int height(BTreeNode<T>* node);
};

template <class T>
BTree<T>::BTree() {}

template <class T>
BTree<T>::~BTree() {}

template <class T>
void preOrder(BTreeNode<T> *node, std::function<void(BTreeNode<T> *)> visitFunc)
{
    if (!node)
        return;
    visitFunc(node);
    preOrder(node->left);
    preOrder(node->right);
}
template <class T>
void inOrder(BTreeNode<T> *node, std::function<void(BTreeNode<T> *)> visitFunc)
{
    if (!node)
        return;
    inOrder(node->left);
    visitFunc(node);
    inOrder(node->right);
}
template <class T>
void postOrder(BTreeNode<T> *node, std::function<void(BTreeNode<T> *)> visitFunc)
{
    if (!node)
        return;
    postOrder(node->left);
    postOrder(node->right);
    visitFunc(node);
}
template<class T> 
 void levelOrder(BTreeNode<T> *node, std::function<void(BTreeNode<T> *)> visitFunc)
{
    std::queue<BTreeNode<T>*> q;
    while(node)
    {
        visitFunc(node);
        if(node->left)q->emplace(node->left);
        if(node->right)q->emplace(node->right);
        if(!q.empty()){
            node=q.front();
            q.pop();
        }else break;
    }
}
template <class T>
int height(BTreeNode<T> *node){
    if(!node)return 0;
    return max(height(node->left),height(node->right))+1;
}