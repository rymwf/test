#include <cstdio>
#include <string>

class Foo
{
    int prop1;
    int prop2;

public:
    class Builder;
    Foo(int prop1_, int prop2_) : prop1(prop1_), prop2(prop2_) {}
    void show()
    {
        printf("prop1: %d,prop2: %d", prop1, prop2);
    }
};

class Foo::Builder{
    int prop1;
    int prop2;
    public:
    Builder& setProp1(int val){prop1=val;return *this;};
    Builder& setProp2(int val){prop2=val;return *this;};
    Foo build(){return Foo(prop1,prop2);}
};

//===============================
class A{
    int a;
    int b;
    public:
    A& seta(int v){a=v;return *this;}
    A& setb(int v){b=v;return *this;}
    void show(){printf("a:%d, b:%d",a,b);}
};

int main()
{
    Foo foo=Foo::Builder().setProp1(1).setProp2(2).build();
    foo.show();
    printf("\n");
    A a=A().seta(1).setb(2);
    a.show();
}
