#include <cstdio>

enum class HelpTopic
{
    NONE,
    APP,
    PRINT,
    DIALOG
};

class HelpHandler
{
protected:
    HelpTopic helpTopic_ = HelpTopic::NONE;

public:
    HelpHandler(HelpTopic topic) : helpTopic_(topic) {}
    virtual void showHelp() = 0;
};

class App : public HelpHandler
{
public:
    App() : HelpHandler(HelpTopic::APP) {}
    void showHelp() override
    {
        switch (helpTopic_)
        {
        case HelpTopic::APP:
            printf("\napp");
            break;
        case HelpTopic::PRINT:
            printf("\nprint");
            break;
        case HelpTopic::DIALOG:
            printf("\ndialog");
            break;
        }
    }
};

class Widget : public HelpHandler
{
protected:
    HelpHandler *parent_ = nullptr;

public:
    Widget(HelpHandler *parent, HelpTopic topic) : parent_(parent), HelpHandler(topic) {}
};

class Button : public Widget
{
public:
    Button(HelpHandler *parent, HelpTopic topic = HelpTopic::NONE) : Widget(parent, topic) {}
    void showHelp() override
    {
        if (helpTopic_ == HelpTopic::NONE)
        {
            parent_->showHelp();
        }
        else
        {
            printf("\n==button help==");
        }
    }
};

class Dialog : public Widget
{
public:
    Dialog(HelpHandler *parent, HelpTopic topic = HelpTopic::NONE) : Widget(parent, topic) {}
    void showHelp() override
    {
        if (int(helpTopic_) == -1)
        {
            parent_->showHelp();
        }
        else
        {
            printf("\n==Dialog help==");
        }
    }
};

int main()
{

    App app = App();
    Dialog a = Dialog(&app, HelpTopic::DIALOG);
    Button b = Button(&a, HelpTopic::PRINT);
    Button b2 = Button(&a);
    Button b3 = Button(&app);
    a.showHelp();
    b.showHelp();
    b2.showHelp();
    b3.showHelp();
}
