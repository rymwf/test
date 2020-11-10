#include <cstdio>
#include <memory>
#include "Singleton.h"

/*
implementation defined in other files
*/

#if 1
#define PLATFORM_X
#else
#define PLATFORM_Y
#endif

class WindowImpl
{
public:
    virtual void SetTitle() = 0;
    virtual void SetSize() = 0;
};

#ifdef PLATFORM_X
class XWindowImpl : public WindowImpl
{
public:
    void SetTitle() override
    {
        printf("==X Window set title==");
    }
    void SetSize() override
    {
        printf("==X Window set size==");
    }
};
#endif
#ifdef PLATFORM_Y
class YWindowImpl : public WindowImpl
{
public:
    void SetTitle() override
    {
        printf("==Y Window set title==");
    }
    void SetSize() override
    {
        printf("==Y Window set size==");
    }
};
#endif

class WindowImplSelector : public Singleton<WindowImplSelector>
{
public:
    std::unique_ptr<WindowImpl> GetWindowImpl()
    {
#ifdef PLATFORM_X
        return std::make_unique<XWindowImpl>();
#elif defined PLATFORM_Y
        return std::make_unique<YWindowImpl>();
#endif
    }
};

class Window
{
    std::unique_ptr<WindowImpl> windowImpl;

public:
    Window() : windowImpl(WindowImplSelector::GetInstancePtr()->GetWindowImpl()) {}
    void Config()
    {
        windowImpl->SetSize();
        windowImpl->SetTitle();
    }
};

int main()
{
    Window window;
    window.Config();
}
