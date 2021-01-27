/**
 * @file BinarySearchTree.h
 * @author yangzs
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <iostream>

namespace yzs
{
    //need to be tested
    template <class Comparable>
    class BinarySearchTree
    {
    private:
        struct BinaryNode
        {
            Comparable element;
            BinaryNode *left;
            BinaryNode *right;
        };

        BinaryNode *root{nullptr};

        const BinaryNode *findMin(BinaryNode *t) const
        {
            if (t == nullptr || t->left == nullptr)
                return t;
            return findMin(t->left);
        }
        const BinaryNode *findMax(BinaryNode *t) const
        {
            if (t != nullptr)
                while (t->right != nullptr)
                    t = t->right;
            return t;
        }
        bool contains(const Comparable &x, BinaryNode *t) const
        {
            if (t == nullptr)
                return false;
            else if (x < t->element)
                return contains(x, t->left);
            else if (x > t->element)
                return contains(x, t->right);
            else
                return true;
        }
        bool empty(BinaryNode *t) const
        {
            return root == nullptr;
        }

        void printTree(std::ostream out, BinaryNode *t) const;

        void clear(BinaryNode *&t)
        {
            if (t != nullptr)
            {
                clear(t->left);
                clear(t->right);
                delete t;
                t = nullptr;
            }
        }
        void insert(const Comparable &x, BinaryNode *&t)
        {
            if (t == nullptr)
                t = new BinaryNode{x};
            else if (t->element > x)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);
        }
        void insert(Comparable &&x, BinaryNode *&t)
        {
            if (t == nullptr)
                t = new BinaryNode{std::move(x)};
            else if (t->element > x)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);
        }
        void remove(const Comparable &x, BinaryNode *&t)
        {
            if (t == nullptr)
                return;
            else if (x < t->element)
                remove(x, t->left);
            else if (x > t->element)
                remove(x, t->right);
            else if (t->left != nullptr && t->right != nullptr)
            {
                t->element = findMin(t->right)->element;
                remove(t->element, t->right);
            }
            else
            {
                BinaryNode *oldNode = t;
                t = t->left == nullptr ? t->right : t->left;
                delete oldNode;
            }
        }
        BinaryNode *clone(BinaryNode *t) const
        {
            if (t == nullptr)
                return nullptr;
            else
                return new BinaryNode{t->element, clone(t->left), clone(t->right)};
        }

    public:
        BinarySearchTree() {}
        BinarySearchTree(const BinarySearchTree &other)
        {
            root = clone(other.root);
        }
        BinarySearchTree(BinarySearchTree &&other)
        {
            root = other.root;
            other.root = nullptr;
        }

        ~BinarySearchTree()
        {
            clear();
        }

        const Comparable &findMin() const
        {
            return findMin(root);
        }
        const Comparable &findMax() const
        {
            return findMax(root);
        }
        bool contains(const Comparable &x) const
        {
            return contains(x, root);
        }
        bool empty() const
        {
            return empty(root);
        }

        void printTree(std::ostream out) const
        {
            printTree(out, root);
        }

        void clear()
        {
            clear(root);
        }
        void insert(const Comparable &x)
        {
            insert(x, root);
        }
        void insert(Comparable &&x)
        {
            insert(x, root);
        }
        void remove(const Comparable &x)
        {
            remove(x, root);
        }

        BinarySearchTree &operator=(const BinarySearchTree &other);
        BinarySearchTree &operator=(BinarySearchTree &&other);
    };

} // namespace yzs
