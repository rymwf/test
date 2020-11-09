#include <cstdio>
#include "Singleton.h"
enum class ShapeType
{
    SPHERE,
    CUBE,
};

class Shape
{
public:
    Shape() = default;
    virtual void Draw() = 0;
};

class Sphere : public Shape
{
public:
    Sphere() = default;
    void Draw() override
    {
        printf("draw Sphere\n");
    }
};
class Cube : public Shape
{
public:
    Cube() = default;
    void Draw() override
    {
        printf("draw Cube\n");
    }
};

class Factory:public Singleton<Factory>
{
public:
    std::shared_ptr<Shape> CreateShape(ShapeType shapetype)
    {
        switch (shapetype)
        {
        case ShapeType::CUBE:
            return std::make_shared<Cube>();
        case ShapeType::SPHERE:
            return std::make_shared<Sphere>();
        }
        return nullptr;
    }
};

int main()
{
    auto a=Factory::GetInstancePtr()->CreateShape(ShapeType::CUBE);
    auto b = Factory::GetInstancePtr()->CreateShape(ShapeType::SPHERE);
    a->Draw();
    b->Draw();

}
