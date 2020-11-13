#include<cstdio>

class AppBase{
    public:
    void run(){
        action1();
        action2();
    }

    void action1(){
        printf("===action 1===");
    }
    virtual void action2()=0;
};

class App:public AppBase{
public:
    void action2()override{
        printf("action2==");
    }
};
int main(){
    App a;
    a.run();
}