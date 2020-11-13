#include <cstdio>
class State
{
public:
    virtual void action1() = 0;
    virtual void action2() = 0;
};
class State1 : public State
{
    static State *instance_;

public:
    static State *instance()
    {
        if (!instance_)
            instance_ = new State1();
        return instance_;
    }
    void action1() override
    {
        printf("state 1 action 1");
    }
    void action2() override
    {
        printf("state 1 action 2");
    }
};
State *State1::instance_ = nullptr;
class State2 : public State
{
    static State *instance_;

public:
    static State *instance()
    {
        if (!instance_)
            instance_ = new State2();
        return instance_;
    }
    void action1() override
    {
        printf("state 2 action 1");
    }
    void action2() override
    {
        printf("state 2 action 2");
    }
};

State *State2::instance_ = nullptr;

class App
{
    State *state_;

public:
    App() : state_(State1::instance()) {}
    void setState(State *state)
    {
        state_ = state;
    }
    void action1()
    {
        state_->action1();
    }
    void action2()
    {
        state_->action2();
    }
};

int main()
{
    App app;
    app.setState(State1::instance());
    app.action1();
    app.setState(State2::instance());
    app.action1();
}