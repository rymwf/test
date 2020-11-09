#include <cstdio>
#include "Singleton.h"

class Object : public Singleton<Object>
{
public:
    void f()
    {
        printf("==========");
    }
};

int main()
{
    auto a = Object::GetInstancePtr();
    a->f();
}