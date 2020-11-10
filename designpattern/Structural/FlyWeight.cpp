#include<cstdio>

class CircleBase{
    int radius=1;
    static CircleBase* instance;
    public:
    static CircleBase* GetInstancePtr(){
        if(instance==nullptr)instance=new CircleBase();
        return instance;
    }
    void draw(){
        printf("circle radius:%d\n",radius);
    }
};

CircleBase *CircleBase::instance = nullptr;

class Circle{
    CircleBase* circleBase;
    int color=2;
    public:    
    Circle(int color_):color(color_),circleBase(CircleBase::GetInstancePtr()){}
    void draw(){
        printf("circle color:%d\n",color);
        circleBase->draw();
    }
};

int main(){
    Circle a(2);
    Circle b(3);
    a.draw();
    b.draw();
}

