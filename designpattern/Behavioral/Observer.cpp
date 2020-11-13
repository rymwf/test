#include <cstdio>
#include <unordered_map>
#include <functional>

//namespace example1
//{
//class Subject;
//class Observer
//{
//
//public:
//    void Update(Subject *subject)
//    {
//        printf("observer===");
//    }
//};
//
//class EventManager
//{
//    std::unordered_multimap<Subject *, Observer *> observers_;
//
//public:
//    void Register(Subject *subject, Observer *observer)
//    {
//        observers_.emplace(subject, observer);
//    }
//    void Unregister(Subject *subject, Observer *observer)
//    {
//        observers_.erase(subject);
//    }
//    void Notify(Subject *subject)
//    {
//        int a = observers_.bucket(subject);
//        for (auto it = observers_.begin(a); it != observers_.end(a); ++it)
//            it->second->Update(subject);
//    }
//};
//class Subject
//{
//    EventManager *eventManager_;
//
//public:
//    Subject(EventManager *manager) : eventManager_(manager) {}
//    void Attach(Observer *observer)
//    {
//        eventManager_->Register(this, observer);
//    }
//    void Action1()
//    {
//        eventManager_->Notify(this);
//    }
//};
//void run()
//{
//    EventManager a;
//    Subject b(&a);
//    Observer c;
//    b.Attach(&c);
//    b.Action1();
//}
//} // namespace example1

namespace example2
{
struct Event
{
    int type;
    Event(int t) : type(t) {}
};

//NOTE: cannot compile with g++ 8.1
template <class... Args>
class EventManager
{
public:
    using handler = std::function<void(Args...)>;
    std::vector<handler> obs_;
    class Observer
    {
    public:
        Observer() {}
        Observer(EventManager *em, handler f)
        {
            em->attach(f);
        }
        void observe(EventManager *em, handler f)
        {
            em->attach(f);
        }
    };

    EventManager()
    {
    }
    void attach(handler f)
    {
        obs_.emplace_back(f);
    }
    void notify(Args... args)
    {
        for (auto &i : obs_)
            i(args...);
    }

protected:
};

void f(Event *event)
{
    printf("\n===event %d ======", event->type);
}

void run()
{
    Event a(2);
    EventManager<Event *> eventManager;
    EventManager<Event *>::Observer ob(&eventManager, f);
    eventManager.notify(&a);
}

} // namespace example2

int main()
{
    //example1::run();
    example2::run();
}
