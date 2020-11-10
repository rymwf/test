#include <memory>
template <class T>
class Singleton
{
    static std::unique_ptr<T> instance_;

protected:
    Singleton() = default;

public:
    static T *GetInstancePtr()
    {
        if (!instance_)
            instance_.reset(new T());
        return instance_.get();
    }
    void ReleaseInstance(){
        if(instance_)
            instance_.~unique_ptr();
    }
};
template <class T>
std::unique_ptr<T> Singleton<T>::instance_;
