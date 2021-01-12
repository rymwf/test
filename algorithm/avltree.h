/**
 * @file avltree.h
 * @author yangzs
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

namespace yzs
{

template <class _T>
struct AVLTreeNode
{
    _T val;
    AVLTreeNode<_T> *left;
    AVLTreeNode<_T> *right;
    int balanceFactor;
};

template <class _T>
class AVLTree
{
    AVLTreeNode<_T> _dummy{};

    constexpr void rotateLL(AVLTreeNode<_T> *node, bool left)
    {
        if (left)
        {
            auto temp = node->left;
            temp->balanceFactor = 0;
            temp->left->balanceFactor = 0;
            node->left = temp->left;
            temp->left = temp->left->right;
            node->left->right = temp;
        }
        else
        {
            auto temp = node->right;
            temp->balanceFactor = 0;
            temp->left->balanceFactor = 0;
            node->right = temp->left;
            temp->left = temp->left->right;
            node->right->right = temp;
        }
    }
    constexpr void rotateLR(AVLTreeNode<_T> *node, bool left)
    {
        if (left)
        {
            auto temp = node->left->left->right;
            node->left->left->right = temp->left;
            temp->left = node->left->left;
            node->left->left = temp->right;
            temp->right = node->left;
            node->left = temp;
            switch (node->left->balanceFactor)
            {
            case 0:
                node->left->left->balanceFactor = 0;
                node->left->right->balanceFactor = 0;
                break;
            case 1:
                node->left->left->balanceFactor = 0;
                node->left->right->balanceFactor = -1;
                break;
            case -1:
                node->left->left->balanceFactor = 1;
                node->left->right->balanceFactor = 0;
                break;
            }
        }
        else
        {
            auto temp = node->right;
            node->right->left->right = temp->left;
            temp->left = node->right->left;
            node->right->left = temp->right;
            temp->right = node->right;
            node->right = temp;
            switch (node->right->balanceFactor)
            {
            case 0:
                node->right->left->balanceFactor = 0;
                node->right->right->balanceFactor = 0;
                break;
            case 1:
                node->right->left->balanceFactor = 0;
                node->right->right->balanceFactor = -1;
                break;
            case -1:
                node->right->left->balanceFactor = 1;
                node->right->right->balanceFactor = 0;
                break;
            }
        }
    }
    constexpr void rotateRR(AVLTreeNode<_T> *node, bool left)
    {
        if (left)
        {
            auto temp = node->left;
            temp->balanceFactor = 0;
            temp->right->balanceFactor = 0;
            node->left = temp->right;
            temp->right = temp->right->left;
            node->left->left = temp;
        }
        else
        {
            auto temp = node->right;
            temp->balanceFactor = 0;
            temp->right->balanceFactor = 0;
            node->right = temp->right;
            temp->right = temp->right->left;
            node->right->left = temp;
        }
    }
    constexpr void rotateRL(AVLTreeNode<_T> *node, bool left)
    {
        if (left)
        {
            auto temp = node->left->left->right;
            node->left->right->left = temp->right;
            temp->right = node->left->right;
            node->left->right = temp->left;
            temp->left = node->left;
            node->left = temp;
            switch (node->left->balanceFactor)
            {
            case 0:
                node->left->left->balanceFactor = 0;
                node->left->right->balanceFactor = 0;
                break;
            case 1:
                node->left->left->balanceFactor = -1;
                node->left->right->balanceFactor = 0;
                break;
            case -1:
                node->left->left->balanceFactor = 0;
                node->left->right->balanceFactor = 1;
                break;
            }
        }
        else
        {
            auto temp = node->right->left->right;
            node->right->right->left = temp->right;
            temp->right = node->right->right;
            node->right->right = temp->left;
            temp->left = node->right;
            node->right = temp;
            switch (node->right->balanceFactor)
            {
            case 0:
                node->right->left->balanceFactor = 0;
                node->right->right->balanceFactor = 0;
                break;
            case 1:
                node->right->left->balanceFactor = -1;
                node->right->right->balanceFactor = 0;
                break;
            case -1:
                node->right->left->balanceFactor = 0;
                node->right->right->balanceFactor = 1;
                break;
            }
        }
    }

public:
    constexpr AVLTree() noexcept {}
    ~AVLTree()
    {
        clear();
    }
    constexpr AVLTreeNode<_T> *getRoot() { return _dummy.left; }

    constexpr void empty() { return _dummy->left == nullptr; }
    //TODO:clear
    constexpr void clear()
    {
    }

    constexpr void push(const _T &val)
    {
        if (!_dummy.left)
        {
            _dummy.left = new AVLTreeNode<_T>{val};
            return;
        }
        else
        {
            AVLTreeNode<_T> *node = _dummy.left;
            AVLTreeNode<_T> *nodepre = &_dummy;
            AVLTreeNode<_T> *nodeA = nullptr;
            AVLTreeNode<_T> *nodeApre = nodepre;
            bool left = true;
            bool templeft = true;
            while (node)
            {
                if (node->balanceFactor & 1)
                {
                    nodeApre = nodepre;
                    nodeA = node;
                    left = templeft;
                }
                nodepre = node;
                if (node->val > val)
                {
                    node = node->left;
                    templeft = true;
                }
                else if (node->val < val)
                {
                    node = node->right;
                    templeft = false;
                }
                else
                {
                    return;
                }
            }
            if (nodepre->val > val)
            {
                nodepre->left = new AVLTreeNode<_T>{val};
            }
            else
            {
                nodepre->right = new AVLTreeNode<_T>{val};
            }

            //update balance factor
            node = nodeA == nullptr ? _dummy.left : nodeA;
            while (node)
            {
                if (node->val > val)
                {
                    node->balanceFactor += 1;
                    node = node->left;
                }
                else if (node->val < val)
                {
                    node->balanceFactor -= 1;
                    node = node->right;
                }
                else
                {
                    break;
                }
            }
            if (nodeA && nodeA->balanceFactor != 0)
            {
                //balance
                if (nodeA->balanceFactor == 2)
                {
                    if (nodeA->left->balanceFactor == 1)
                    {
                        //LL
                        rotateLL(nodeApre, left);
                    }
                    else
                    {
                        //LR
                        rotateLR(nodeApre, left);
                    }
                }
                else if (nodeA->balanceFactor == -2)
                {
                    if (nodeA->right->balanceFactor == -1)
                    {
                        //RR
                        rotateRR(nodeApre, left);
                    }
                    else
                    {
                        //RL
                        rotateRL(nodeApre, left);
                    }
                }
            }
        }
    }
};

} // namespace yzs
