#include <string>
#include <iostream>
#include <vector>
#include <fstream>


std::string handleDuplicateFileName(const std::string& baseName);

class Image {
protected:
    std::string magicNumber;
    int width;
    int height;
    int maxColor;

public:
    Image();
    virtual ~Image();

    virtual void initialize(int w, int h);
    virtual bool loadImage(const std::string& filename) = 0;
    virtual bool saveImage(const std::string& inputfilename) = 0;
    virtual void invert() = 0;
    virtual void drawRectangle(int width, int height, int rectWidth, int rectHeight, bool drawBorder, bool On) = 0;

    int GetWidth();
    int Getheight();
};

class PPMImage : public Image
{
private:
    struct Pixel {
        unsigned char r, g, b;
    };
    std::vector <Pixel> pixels;
public:
    PPMImage();
    bool loadImage(const std::string& filename) override;
    bool saveImage(const std::string& inputfilename) override;
    void invert() override;
    void drawRectangle(int width, int height, int rectWidth, int rectHeight, bool drawBorder, bool On) override;
};

class PGMImage : public Image
{
private:
    struct Pixel {
        unsigned char gray;
    };
    std::vector<Pixel> pixels;
public:
    PGMImage();
    bool loadImage(const std::string& filename) override;
    bool saveImage(const std::string& inputfilename) override;
    void invert() override;
    void drawRectangle(int width, int height, int rectWidth, int rectHeight, bool drawBorder, bool On) override;

};

void processRectangleDrawing();
void processImageInversion(const std::string& directory, const std::vector<std::string>& imageList);
void drawRectangleOnSelectedImage(const std::string& directory, const std::vector<std::string>& imageList);
