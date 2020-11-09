#include <cstdio>
enum class ShowType
{
    movie,
    music
};

class App
{
public:
    virtual void Show(ShowType tpye) = 0;
};

class MusicApp
{
public:
    void ShowNM()
    {
        printf("==show Music==");
    }
};

class AppAdatper : public App
{
    MusicApp musicApp;

public:
    void Show(ShowType type) override
    {
        switch (type)
        {
        case ShowType::music:
            musicApp.ShowNM();
            break;
        }
    }
};

class MovieApp : public App
{
    AppAdatper appAdatper;

public:
    void Show(ShowType type) override
    {
        switch (type)
        {
        case ShowType::movie:
            printf("==Show Movie==");
            break;
        case ShowType::music:
            appAdatper.Show(type);
            break;
        }
    }
};

int main()
{
    MovieApp a;
    a.Show(ShowType::movie);
    a.Show(ShowType::music);
}