#include <cstdio>
#include <vector>

class Leaf1
{
public:
    void draw() { printf("=draw leaf1==\n"); }
};
class Leaf2
{
public:
    void draw() { printf("=draw leaf2==\n"); }
};

class Composite
{
    std::vector<Composite *> children;
    Composite *parent;
    Leaf1 leaf1;
    Leaf2 leaf2;

public:
    void addChildren(Composite *comp)
    {
        printf("==add children=");
        children.emplace_back(comp);
    }
    void setParent(Composite *comp)
    {
        printf("==set parent=");
    }
    void removeChildren(Composite *comp)
    {
        printf("==remove chilren=");
    }
    void operation()
    {
        printf("==aa==\n");
        for (auto &i : children)
            i->operation();
    }
};

int main()
{

    Composite a;
    Composite b;
    Composite c;
    a.addChildren(&b);
    b.addChildren(&c);
    a.operation();
}
