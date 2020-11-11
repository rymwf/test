#include <cstdio>
#include <string>
/*
virtual proxy
*/

class Image
{
public:
    virtual void draw() = 0;
    virtual int getExtent() = 0;
};
class RealImage : public Image
{
    int extent = 0;

public:
    RealImage(const char *filename) {}
    virtual void draw() override {}
    virtual int getExtent() override { return extent; }
};

//
class ImageProxy : public Image
{
    Image *image = nullptr;
    std::string fileName;
    int extent = 0;
    Image *getImage()
    {
        if (image == nullptr)
            image = new RealImage(&fileName[0]);
        return image;
    }

public:
    ImageProxy(const char *filename) : fileName(filename) {}
    virtual void draw() override
    {
        getImage()->draw();
    }
    virtual int getExtent() override
    {
        if (!extent)
            extent = getImage()->getExtent();
        return extent;
    }
};

int main()
{
    Image *a = new ImageProxy("imagefilename");
    a->getExtent();
    a->draw();
}