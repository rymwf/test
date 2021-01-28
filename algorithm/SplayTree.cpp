/**
 * @file SplayTree.cpp
 * @author yangzs
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>

namespace yzs
{
    //need to be tested
    template <class Comparable>
    class SplayTree
    {
    private:
        struct BinaryNode
        {
            Comparable element;
            BinaryNode *left;
            BinaryNode *right;
        };

        BinaryNode *root{nullptr};

        void rotateLeft(BinaryNode *&k2)
        {
            BinaryNode *k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2 = k1;
        }
        void rotateRight(BinaryNode *&k2)
        {
            BinaryNode *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2 = k1;
        }

        //test
        int find(const Comparable &x, BinaryNode *&t)
        {
            if (t == nullptr)
                return INT_MIN;
            else if (t->element > x)
            {
                rotateRight(t);
                return find(x, t) + 1;
            }
            else if (t->element < x)
            {
                rotateLeft(t);
                return find(x, t) + 1;
            }
            else
                return 0;
        }
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

        void printTree(std::ostream &out, BinaryNode *t) const
        {
            if (t != nullptr)
            {
                printTree(out, t->left);
                out << t->element << " ";
                printTree(out, t->right);
            }
        }

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
        SplayTree() {}
        SplayTree(const SplayTree &other)
        {
            root = clone(other.root);
        }
        SplayTree(SplayTree &&other)
        {
            root = other.root;
            other.root = nullptr;
        }

        ~SplayTree()
        {
            clear();
        }

        int height(BinaryNode *t) const
        {
            return t == nullptr ? -1 : max(height(t->left), height(t->right)) + 1;
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

        int find(const Comparable& x)
        {
            return find(x, root);
        }

        SplayTree &operator=(const SplayTree &other);
        SplayTree &operator=(SplayTree &&other);
    };

} // namespace yzs

#include<vector>

int main(){

    std::vector a{3, 4, 5, 2, 1, 6, 7, 8, 4, 3, 1, 2, 0, 33, 22, 11, 44, 55, 66, 44, 23, 1, 12};
    yzs::SplayTree<int> splaytree;
    for(auto e:a)
        splaytree.insert(e);
    splaytree.printTree(std::cout);

    std::cout << std::endl;
    std::cout << splaytree.find(7) << std::endl;
    std::cout << splaytree.find(7) << std::endl;
    std::cout << splaytree.find(7) << std::endl;
    std::cout << splaytree.find(33) << std::endl;
    std::cout << splaytree.find(33) << std::endl;
    std::cout << splaytree.find(7) << std::endl;
    std::cout << splaytree.find(8) << std::endl;
}

