#include<cstdio>
#include <unordered_map>
#include<vector>
#include<unordered_set>

class Flyweight{
    int intrinsicState0=0;// sharable
public:
    Flyweight(int state):intrinsicState0(state){}
    void draw(){
        printf("state:%d\n",intrinsicState0);
    }
};

class FlyweightFactory{
    std::unordered_map<int,Flyweight*> mtable;
    int getId(int state){
        return state;
    }
public:
   Flyweight* createFlyweight(int state){
       int id=getId(state);
       if(mtable.find(id)==mtable.end())
       {
           printf("create new flyweight\n");
           mtable[id] = new Flyweight(state);
           return mtable[id];
       }
       return mtable[id];
   };
};

int main(){
    auto factory=FlyweightFactory();
    auto a1= factory.createFlyweight(2);
    auto a2= factory.createFlyweight(3);
    auto a3= factory.createFlyweight(2);
    a1->draw();
    a2->draw();
    a3->draw();

};
