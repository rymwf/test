#include <cstdio>

class Shape
{
public:
    virtual void draw() = 0;
};

class Cube : public Shape
{
public:
    void draw() override
    {
        printf("==draw cube==\n");
    }
};

class ShapeDecorator : public Shape
{
protected:
    Shape *shapePtr;
    ShapeDecorator() = delete;
    ShapeDecorator(Shape *shape) : shapePtr(shape) {}

public:
    void draw() override
    {
        shapePtr->draw();
    }
};

class CubeDecorator : public ShapeDecorator
{
    void drawSmile()
    {
        printf("draw smile\n");
    }

public:
    CubeDecorator(Cube *cube) : ShapeDecorator(cube) {}
    void draw() override
    {
        shapePtr->draw();
        drawSmile();
    }
};

int main()
{
    Shape *a = new CubeDecorator(new Cube());
    a->draw();
}
