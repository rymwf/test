#include <cstdio>
#include <vector>
class Receiver
{
public:
    void doCommandSimple()
    {
        printf("\nreceiver A action commandSimple");
    }
    void doCommand1()
    {
        printf("\nreceiver A action command1");
    }
    void doCommand2()
    {
        printf("\nreceiver A action command2");
    }
};
class Command
{
protected:
    Receiver *receiver_;

public:
    Command(Receiver *receiver) : receiver_(receiver) {}
    virtual void execute() = 0;
};
//invoke operation
class ConcreteCommand1 : public Command
{
public:
    ConcreteCommand1(Receiver *r) : Command(r) {}
    void execute() override
    {
        ///        printf("\nexecute 1");
        receiver_->doCommand1();
    }
};
class ConcreteCommand2 : public Command
{
public:
    ConcreteCommand2(Receiver *r) : Command(r) {}
    void execute() override
    {
        receiver_->doCommand2();
    }
};

//commands that are not undoable and do not require arguments
template <class T>
class SimpleCommand : public Command
{
public:
    SimpleCommand(T *receiver) : Command(receiver) {}
    void execute() override
    {
        receiver_->doCommandSimple();
    }
};
//used for undo and redo command
class Invoker
{
    std::vector<Command *> commandList;

public:
    void processCommand(Command *command)
    {
        commandList.emplace_back(command);
        command->execute();
    }
    void redo() {}
    void undo() {}
};

int main()
{
    //create a concrete command and specifies its receiver
    auto a = Receiver();
    ConcreteCommand1 *c1 = new ConcreteCommand1(&a);
    ConcreteCommand2 *c2 = new ConcreteCommand2(&a);
    SimpleCommand<Receiver> *c3 = new SimpleCommand<Receiver>(&a);

    Invoker invoker = Invoker();
    invoker.processCommand(c1);
    invoker.processCommand(c2);
    invoker.processCommand(c3);
}