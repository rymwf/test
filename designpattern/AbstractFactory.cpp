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

class SphereA : public Shape
{
public:
    SphereA() = default;
    void Draw() override
    {
        printf("draw SphereA\n");
    }
};
class CubeA : public Shape
{
public:
    CubeA() = default;
    void Draw() override
    {
        printf("draw CubeA\n");
    }
};

enum class FactoryType
{
    A,
    B
};

class Factory
{
public:
    virtual std::shared_ptr<Shape> CreateShape(ShapeType shapetype) = 0;
};

class FactoryA : public Factory, public Singleton<FactoryA>
{
public:
    std::shared_ptr<Shape> CreateShape(ShapeType shapetype)
    {
        switch (shapetype)
        {
        case ShapeType::CUBE:
            return std::make_shared<CubeA>();
        case ShapeType::SPHERE:
            return std::make_shared<SphereA>();
        }
        return nullptr;
    }
};
class FactoryB : public Factory, public Singleton<FactoryB>
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

class FactoryProducer : public Singleton<FactoryProducer>
{
public:
    Factory *GetFactory(FactoryType type)
    {
        switch (type)
        {
        case FactoryType::A:
            return FactoryA::GetInstancePtr();
        case FactoryType::B:
            return FactoryB::GetInstancePtr();
        }
        return nullptr;
    }
};

int main()
{
    auto a = FactoryProducer::GetInstancePtr()->GetFactory(FactoryType::A);
    auto b = FactoryProducer::GetInstancePtr()->GetFactory(FactoryType::B);
    auto shape1 = a->CreateShape(ShapeType::CUBE);
    auto shape2 = b->CreateShape(ShapeType::CUBE);
    shape1->Draw();
    shape2->Draw();
}