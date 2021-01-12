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
namespace yzs{

template <class T>
struct BinTreeNode
{
    T val;
    BinTreeNode *left;
    BinTreeNode *right;
};

//    static_assert(std::is_arithmetic_v<T>,"BinTree only support arithmetic type");

#if 1
template <class T>
class BinTreeView
{
public:
    static void preOrder(T *node, std::function<void(T *)> visitFunc);
    static void inOrder(T *node, std::function<void(T *)> visitFunc);
    static void postOrder(T *node, std::function<void(T *)> visitFunc);
    static void levelOrder(T *node, std::function<void(T *)> visitFunc);
    static int height(T *node);
};

template <class T>
void BinTreeView<T>::preOrder(T *node, std::function<void(T *)> visitFunc)
{
    if (!node)
        return;
    visitFunc(node);
    preOrder(node->left);
    preOrder(node->right);
}
template <class T>
void BinTreeView<T>::inOrder(T *node, std::function<void(T *)> visitFunc)
{
    if (!node)
        return;
    inOrder(node->left);
    visitFunc(node);
    inOrder(node->right);
}
template <class T>
void BinTreeView<T>::postOrder(T *node, std::function<void(T *)> visitFunc)
{
    if (!node)
        return;
    postOrder(node->left);
    postOrder(node->right);
    visitFunc(node);
}
template <class T>
void BinTreeView<T>::levelOrder(T *node, std::function<void(T *)> visitFunc)
{
    std::queue<T *> q;
    while (node)
    {
        visitFunc(node);
        if (node->left)
            q.emplace(node->left);
        if (node->right)
            q.emplace(node->right);
        if (!q.empty())
        {
            node = q.front();
            q.pop();
        }
        else
            break;
    }
}
template <class T>
int BinTreeView<T>::height(T *node)
{
    if (!node)
        return 0;
    return max(height(node->left), height(node->right)) + 1;
}
#endif

#if 0
template <class T>
class BinTreeView
{
public:
    BinTreeView() {}
    virtual ~BinTree() {}
    void preOrder(BinTreeNode<T> *node);
    void inOrder(BinTreeNode<T> *node);
    void postOrder(BinTreeNode<T> *node);
    void levelOrder(BinTreeNode<T> *node);

    virtual void visit(BinTreeNode<T> *node);
    int height(BinTreeNode<T> *node);
};

template <class T>
void BinTreeView<T>::preOrder(BinTreeNode<T> *node)
{
    if (!node)
        return;
    visit(node);
    preOrder(node->left);
    preOrder(node->right);
}
template <class T>
void BinTreeView<T>::inOrder(BinTreeNode<T> *node)
{
    if (!node)
        return;
    inOrder(node->left);
    visit(node);
    inOrder(node->right);
}
template <class T>
void BinTreeView<T>::postOrder(BinTreeNode<T> *node)
{
    if (!node)
        return;
    postOrder(node->left);
    postOrder(node->right);
    visit(node);
}
template <class T>
void BinTreeView<T>::levelOrder(BinTreeNode<T> *node)
{
    std::queue<BinTreeNode<T> *> q;
    while (node)
    {
        visit(node);
        if (node->left)
            q->emplace(node->left);
        if (node->right)
            q->emplace(node->right);
        if (!q.empty())
        {
            node = q.front();
            q.pop();
        }
        else
            break;
    }
}
template <class T>
int BinTreeView<T>::height(BinTreeNode<T> *node)
{
    if (!node)
        return 0;
    return max(height(node->left), height(node->right)) + 1;
}
#endif
}