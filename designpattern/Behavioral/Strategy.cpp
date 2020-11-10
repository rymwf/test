#include <cstdio>
/*
could use templete
*/

class Strategy
{
public:
    virtual void AlogrithmInterface() = 0;
};

class ConcreteStrategyA : public Strategy
{
public:
    void AlogrithmInterface() override
    {
        printf("===ConcreteStrategyA==");
    }
};
class ConcreteStrategyB : public Strategy
{
public:
    void AlogrithmInterface() override
    {
        printf("===ConcreteStrategyB==");
    }
};

class Context
{
    Strategy *strategy;

public:
    Context(Strategy *strategy_) : strategy(strategy_) {}
    void run()
    {
        strategy->AlogrithmInterface();
    }
};
int main()
{
    Context *ctx = new Context(new ConcreteStrategyA());
    ctx->run();
}
