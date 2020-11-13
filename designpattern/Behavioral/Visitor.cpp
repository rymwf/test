#include<cstdio>
class Element;
class Visitor{
    public:
    virtual void viewElement(Element* ele)=0;
};
class Element{
    public:
    virtual void action1()=0;
    virtual void action2()=0;
    void accept(Visitor* visitor){
        visitor->viewElement(this);
    }
};
class ElementA:public Element{
    public:
    void action1()override{
        printf("=element A action 1=");
    }
    void action2()override{
        printf("=element A action 2=");
    }
};

class VisitorA:public Visitor{
    public:
    void viewElement(Element* ele){
        ele->action1();
    }
};
class VisitorB:public Visitor{
    public:
    void viewElement(Element* ele){
        ele->action2();
    }
};
int main(){
    VisitorA va;
    VisitorB vb;
    ElementA a; 
    a.accept(&va);
    a.accept(&vb);
}
