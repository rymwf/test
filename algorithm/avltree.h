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

    template <class Comparable>
    class AvlTree
    {
    private:
        struct AvlNode
        {
            Comparable element;
            AvlNode *left;
            AvlNode *right;
            int height;
        };

        AvlNode *root{nullptr};
        static constexpr int ALLOW_IMBALANCE = 1;

        void rotate(AvlNode *&k2)
        {
            AvlNode *k1;
            int hl = height(k2->left);
            int hr = height(k2->right);
            if (hl > hr)
            {
                k1 = k2->left;
                k2->left = k1->right;
                k1->right = k2;
            }
            else if (hl < hr)
            {
                k1 = k2->right;
                k2->right = k1->left;
                k1->left = k2;
            }
            k2->height = std::max(height(k2->left), height(k2->right)) + 1;
            k1->height = std::max(height(k1->left), height(k1->right)) + 1;
            k2 = k1;
        }

        void balance(AvlNode *&t)
        {
            if (t == nullptr)
                return;
            int hl = height(t->left);
            int hr = height(t->right);
            if (hl - hr > ALLOW_IMBALANCE && height(t->left->left) < height(t->left->right))
                rotate(t->left);
            else if (hr - hl > ALLOW_IMBALANCE && height(t->right->left) > height(t->right->right))
                rotate(t->right);
            else
            {
                t->height = std::max(hl, hr) + 1;
                return;
            }
            rotate(t);
        }

        const AvlNode *findMin(AvlNode *t) const
        {
            if (t == nullptr || t->left == nullptr)
                return t;
            return findMin(t->left);
        }
        const AvlNode *findMax(AvlNode *t) const
        {
            if (t != nullptr)
                while (t->right != nullptr)
                    t = t->right;
            return t;
        }
        bool contains(const Comparable &x, AvlNode *t) const
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
        bool empty(AvlNode *t) const
        {
            return root == nullptr;
        }

        void printTree(std::ostream &out, AvlNode *t) const
        {
            if (t != nullptr)
            {
                printTree(out, t->left);
                out << t->element << std::endl;
                printTree(out, t->right);
            }
        }

        void clear(AvlNode *&t)
        {
            if (t != nullptr)
            {
                clear(t->left);
                clear(t->right);
                delete t;
                t = nullptr;
            }
        }
        void insert(const Comparable &x, AvlNode *&t)
        {
            if (t == nullptr)
                t = new AvlNode{x};
            else if (t->element > x)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);
            balance(t);
        }
        void insert(Comparable &&x, AvlNode *&t)
        {
            if (t == nullptr)
                t = new AvlNode{std::move(x)};
            else if (t->element > x)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);
            balance(t);
        }
        void remove(const Comparable &x, AvlNode *&t)
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
                AvlNode *oldNode = t;
                t = t->left == nullptr ? t->right : t->left;
                delete oldNode;
            }
            balance(t);
        }
        AvlNode *clone(AvlNode *t) const
        {
            if (t == nullptr)
                return nullptr;
            else
                return new AvlNode{t->element, clone(t->left), clone(t->right)};
        }

    public:
        AvlTree() {}
        AvlTree(const AvlTree &other)
        {
            root = clone(other.root);
        }
        AvlTree(AvlTree &&other)
        {
            root = other.root;
            other.root = nullptr;
        }

        ~AvlTree()
        {
            clear();
        }

        int height(AvlNode *t) const
        {
            return t == nullptr ? -1 : t->height;
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

        void printTree(std::ostream &out) const
        {
            if (empty())
                out << "empty tree";
            else
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

        AvlTree &operator=(const AvlTree &other);
        AvlTree &operator=(AvlTree &&other);
    };

} // namespace yzs
