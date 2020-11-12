#include<cstdio>
#include<unordered_map>

class DialogDirector;
class Widget{
    protected:
    DialogDirector* director_;
    const char* name_; 
public:
    virtual void Changed();
    Widget(const char* name, DialogDirector* director);
    const char* GetName(){return name_;}
};
class DialogDirector{
    std::unordered_map<Widget*,int> widgets;
    int SetId(){
        static int id=0;
        id++;
        return id;
    }
public:
    DialogDirector() { }
    ~DialogDirector() {}
    void AddWidget(Widget* widget){
        static int id=0;
        widgets[widget]=id;
        id++;
    }
    void ShowDialog();
    void WidgetChanged(Widget *widget)
    {
        printf("\nwidget id:%d",widgets[widget]);
    }
};

void Widget::Changed(){
    director_->WidgetChanged(this);
}
Widget::Widget(const char *name, DialogDirector *director) : name_(name), director_(director)
{
    director_->AddWidget(this);
}
class ListBox : public Widget
{
public:
    ListBox(const char* name,DialogDirector* director):Widget(name,director){}
    void Action(){
      Changed();  
    }
};

class Button:public Widget{
public:
    Button(const char* name,DialogDirector* director):Widget(name,director){}
    void Action(){
      Changed();  
    }
};


int main(){
    DialogDirector a;
    ListBox b("bbb",&a);
    Button c("ccc",&a);
    b.Action();
    c.Action();
}

