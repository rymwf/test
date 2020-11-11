/*
*/
#include<cstdio>
#include<unordered_map>

class Prototype{
public:
    virtual Prototype* clone()=0;
};
class ConcretePrototype1:public Prototype{
    public:
    Prototype* clone()override{
        printf("implement clone concrete 1");
        return this;
    }
};
class ConcretePrototype2:public Prototype{
    public:
    Prototype* clone()override{
        printf("implement clone concrete 2");
        return this;
    }
};

class PrototypeManager{
    std::unordered_map<int,Prototype*> mTable;
public:
    PrototypeManager(){
        mTable[1]=new ConcretePrototype1();
        mTable[2]=new ConcretePrototype2();
    } 
    Prototype* GetPrototype(int i){
        return mTable[i]->clone();
    }
};

int main(){
    PrototypeManager m;
    auto a=m.GetPrototype(1);
    auto b=m.GetPrototype(2);
}

