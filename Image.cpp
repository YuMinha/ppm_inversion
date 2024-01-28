#pragma once

#include "Image.h"
#include "UserInterface.h"

void Image::initialize(int w, int h)
{
    this->width = w;
    this->height = h;
}
Image::Image() {}
Image::~Image() {}
int Image::GetWidth()
{
    return this->width;
}
int Image::Getheight()
{
    return this->height;
}

//�ߺ��Ǵ� �̸��� ���� �����ϴ� �Լ�
std::string handleDuplicateFileName(const std::string& baseName) {
    std::string newName = baseName;
    int count = 1;

    while (std::ifstream(newName)) {
        // ���� �̸� Ȯ���ڸ� �и�
        size_t lastDot = baseName.find_last_of('.');
        std::string nameWithoutExtension = baseName.substr(0, lastDot);
        std::string extension = baseName.substr(lastDot + 1);

        newName = nameWithoutExtension + "(" + std::to_string(count) + ")." + extension;
        count++;
    }

    return newName;
}

PPMImage::PPMImage()
{
    magicNumber = "P6";
    maxColor = 255;
}
bool PPMImage::loadImage(const std::string& filename)
{
    std::ifstream input(filename, std::ios::binary);
    if (!input) {
        std::cerr << "������ �� �� �����ϴ�." << std::endl;
        return false;
    }

    input >> magicNumber >> width >> height >> maxColor;

    if (maxColor != 255) {
        std::cerr << "�ùٸ� PPM ������ �ƴմϴ�." << std::endl;
        return false;
    }

    pixels.resize(width * height);

    input.ignore(); // �� ĭ ���� ����
    input.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * sizeof(Pixel));

    return true;
}
bool PPMImage::saveImage(const std::string& inputfilename)
{
    std::string filename = handleDuplicateFileName(inputfilename);

    std::ofstream output(filename, std::ios::binary);
    if (!output) {
        std::cerr << "��� ������ �� �� �����ϴ�." << std::endl;
        return false;
    }

    output << magicNumber << "\n" << width << " " << height << "\n" << maxColor << "\n";
    output.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(Pixel));

    return true;
}
void PPMImage::invert()
{
    for (auto& pixel : pixels) {
        pixel.r = 255 - pixel.r;
        pixel.g = 255 - pixel.g;
        pixel.b = 255 - pixel.b;
    }
}
void PPMImage::drawRectangle(int width, int height, int rectWidth, int rectHeight, bool drawBorder,bool On)
{
    this->width = width;
    this->height = height;

    // �Էµ� �簢�� ũ�Ⱑ �̹��� ũ�⸦ �ʰ��ϸ� ũ�⸦ ����
    rectWidth = min(rectWidth, width);
    rectHeight = min(rectHeight, height);

    // �̹����� �߽� ��ǥ ���
    int centerX = width / 2;
    int centerY = height / 2;

    // �簢���� ���� ��ǥ ��� (�߽� ��������)
    int startX = centerX - rectWidth / 2;
    int startY = centerY - rectHeight / 2;
    ;
    pixels.resize(width * height);

    Pixel color;
    int r, g, b;
    std::cout << "�׵θ� or �簢���� ���� �Է��ϼ���(r, g, b ��) : ";
    std::cin >> r >> g >> b;
    color.r = static_cast<unsigned char>(r);
    color.g = static_cast<unsigned char>(g);
    color.b = static_cast<unsigned char>(b);
    
    if (!On) 
    {
        for (auto& pixel : pixels)
        {
            pixel.r = 255;
            pixel.g = 255;
            pixel.b = 255;
        }
    }

    int index = 0;
    // �簢�� �׸���
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            index = y * width + x;
            Pixel& pixel = pixels[index];
            if (x >= startX && x < startX + rectWidth && y >= startY && y < startY + rectHeight) {
                // �簢�� ���� �ȼ�
                if (drawBorder) {
                    // �׵θ��� �׸��� ���
                    if (x == startX || x == startX + rectWidth - 1 || y == startY || y == startY + rectHeight - 1) {
                        // �׵θ� �ȼ�
                        pixel.r = color.r;
                        pixel.g = color.g;
                        pixel.b = color.b;
                    }
                }
                else {
                    // ���θ� ä��� ���
                    pixel.r = color.r;
                    pixel.g = color.g;
                    pixel.b = color.b;
                }
            }
        }
    }
}

PGMImage::PGMImage()
{
    magicNumber = "P5";
    maxColor = 255;
}
bool PGMImage::loadImage(const std::string& filename)
{
    std::ifstream input(filename, std::ios::binary);
    if (!input) {
        std::cerr << "������ �� �� �����ϴ�." << std::endl;
        return false;
    }

    input >> magicNumber >> width >> height >> maxColor;

    if (maxColor != 255) {
        std::cerr << "�ùٸ� �̹��� ������ �ƴմϴ�." << std::endl;
        return false;
    }

    pixels.resize(width * height);

    input.ignore();
    input.read(reinterpret_cast<char*>(pixels.data()), pixels.size());

    return true;
}
bool PGMImage::saveImage(const std::string& inputfilename)
{
    /*
    * �ݺ��ؼ� ���� �� �����ϸ� ������
    * �ߺ��� �̸� ó�� �ʿ�
    */
    std::string filename = handleDuplicateFileName(inputfilename);
    std::ofstream output(filename, std::ios::binary);
    if (!output) {
        std::cerr << "��� ������ �� �� �����ϴ�." << std::endl;
        return false;
    }

    output << magicNumber << "\n" << width << " " << height << "\n" << maxColor << "\n";
    output.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());

    return true;
}
void PGMImage::invert()
{
    for (auto& pixel : pixels) {
        pixel.gray = 255 - pixel.gray;
    }
}
void PGMImage::drawRectangle(int width, int height, int rectWidth, int rectHeight, bool drawBorder, bool On)
{
    this->width = width;
    this->height = height;

    // �Էµ� �簢�� ũ�Ⱑ �̹��� ũ�⸦ �ʰ��ϸ� ũ�⸦ ����
    rectWidth = min(rectWidth, width);
    rectHeight = min(rectHeight, height);

    // �̹����� �߽� ��ǥ ���
    int centerX = width / 2;
    int centerY = height / 2;

    // �簢���� ���� ��ǥ ��� (�߽� ��������)
    int startX = centerX - rectWidth / 2;
    int startY = centerY - rectHeight / 2;
    ;
    pixels.resize(width * height);

    int br;
    std::cout << "�׵θ� or �簢���� ��⸦ �Է��ϼ���(0~255 : Ŭ ���� ����) : ";
    std::cin >> br;
    
    if (!On)
    {
        for (auto& pixel : pixels)
        {
            pixel.gray = 255 - br;
        }
    }

    int index = 0;
    // �簢�� �׸���
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            index = y * width + x;
            Pixel& pixel = pixels[index];
            if (x >= startX && x < startX + rectWidth && y >= startY && y < startY + rectHeight) {
                // �簢�� ���� �ȼ�
                if (drawBorder) {
                    // �׵θ��� �׸��� ���
                    if (x == startX || x == startX + rectWidth - 1 || y == startY || y == startY + rectHeight - 1) {
                        // �׵θ� �ȼ�
                        pixel.gray = br;
                    }
                }
                else {
                    // ���θ� ä��� ���
                    pixel.gray = br;
                }
            }
        }
    }
}

void processImageInversion(const std::string& directory, const std::vector<std::string>& imageList) {
    int selectedIndex = selectImage(imageList);
    if (selectedIndex == -1) return;
    std::string imagePath = directory + "/" + imageList[selectedIndex];

    // �̹��� Ȯ���ڸ� �м��Ͽ� PPM �Ǵ� PGM Ŭ������ ����
    std::string extension = imagePath.substr(imagePath.find_last_of('.') + 1);
    Image* image;
    if (extension == "ppm") {
        image = new PPMImage();
    }
    else if (extension == "pgm") {
        image = new PGMImage();
    }
    else {
        std::cout << "�������� �ʴ� �̹��� �����Դϴ�." << std::endl;
        return;
    }

    if (image->loadImage(imagePath)) {
        image->invert();
        std::string invertedFilename = imagePath.substr(0, imagePath.find_last_of('.')) + "_inverted." + extension;
        if (image->saveImage(invertedFilename)) {
            std::cout << "�̹��� ������ �Ϸ�Ǿ����ϴ�." << std::endl;
        }
        else {
            std::cout << "�̹��� ���� ����" << std::endl;
        }
        delete image;
    }
    else {
        std::cout << "�̹��� �ҷ����� ����" << std::endl;
        delete image;
    }
}
void processRectangleDrawing() {
    int imageWidth, imageHeight;
    int rectWidth, rectHeight;
    bool drawBorder;
    bool isColor;
    bool On = false;
    std::string file = "rectangle_Draw", extention;

    std::cout << "���� ������ �������ּ��� (1: �÷� �̹���, 0 : ��� �̹���) : ";

    if (!(std::cin >> isColor)) {
        std::cerr << "�ùٸ��� ���� �Է��Դϴ�. ���� 0 �Ǵ� 1�� �Է����ּ���." << std::endl;
        std::cin.clear(); // ��Ʈ���� ���� �÷��� �ʱ�ȭ
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // �Է� ���� ����
        return; // ���α׷� ���� �Ǵ� ���� ó��
    }

    Image* image;
    if (isColor==1) {
        image = new PPMImage();
        extention = ".ppm";
    }
    else if(isColor==0) {
        image = new PGMImage();
        extention = ".pgm";
    }
    else
    {
        std::cerr << "�ùٸ��� ���� �����Դϴ�. 0Ȥ�� 1�� �Է����ּ���.";
        return ;
    }

    std::cout << "�̹��� �ʺ� �Է��ϼ��� (�ִ� 255): ";
    std::cin >> imageWidth;
    std::cout << "�̹��� ���̸� �Է��ϼ��� (�ִ� 255): ";
    std::cin >>imageHeight;

    if (imageWidth > 256 || imageHeight > 256)
    {
        std::cerr << "�̹����� ũ�Ⱑ �ʹ� Ů�ϴ�.\n";
        return;
    }

    std::cout << "�簢�� �ʺ� �Է��ϼ���: ";
    std::cin >> rectWidth;
    std::cout << "�簢�� ���̸� �Է��ϼ���: ";
    std::cin >> rectHeight;

    if (rectWidth > imageWidth || rectHeight > imageHeight) {
        std::cerr << "�簢���� ũ�Ⱑ �ʹ� Ů�ϴ�.\n";
        return;
    }

    std::cout << "�簢�� ���¸� ������ �ּ��� (1: �׵θ���, 0: ���� ä���): ";
    std::cin >> drawBorder;

    image->initialize(imageWidth, imageHeight);

    image->drawRectangle(imageWidth, imageHeight, rectWidth, rectHeight, drawBorder,On);
    // �̹��� ����
    std::string invertedFilename = file + extention;
    if (image->saveImage(invertedFilename)) {
        std::cout << "�̹��� ������ �Ϸ�Ǿ����ϴ�." << std::endl;
    }
    else {
        std::cout << "�̹��� ���� ����" << std::endl;
    }
    delete image;
}
void drawRectangleOnSelectedImage(const std::string& directory, const std::vector<std::string>& imageList) {
    bool On = true;
    int selectedIndex = selectImage(imageList);
    if (selectedIndex == -1) return;
    std::string imagePath = directory + "/" + imageList[selectedIndex];

    // �̹��� Ȯ���ڸ� �м��Ͽ� PPM �Ǵ� PGM Ŭ������ ����
    std::string extension = imagePath.substr(imagePath.find_last_of('.') + 1);
    Image* image;
    if (extension == "ppm") {
        image = new PPMImage();
    }
    else if (extension == "pgm") {
        image = new PGMImage();
    }
    else {
        std::cout << "�������� �ʴ� �̹��� �����Դϴ�." << std::endl;
        return;
    }

    if (image->loadImage(imagePath)) {
        // ����ڷκ��� �簢�� ���� �Է� �ޱ�
        int rectWidth, rectHeight;
        bool drawBorder;
        int w, h;
        w = image->GetWidth();
        h = image->Getheight();
        std::cout << "�簢�� �ʺ�� ���̸� �Է��ϼ��� (�ִ� " << w<< "x" << h << "): ";
        std::cin >> rectWidth >> rectHeight;

        if (rectWidth > w || rectHeight > h) {
            std::cerr << "�簢���� ũ�Ⱑ �̹����� �ʰ��մϴ�." << std::endl;
            delete image;
            return;
        }

        std::cout << "�簢�� ���¸� ������ �ּ��� (1: �׵θ���, 0: ���� ä���): ";
        std::cin >> drawBorder;

        // �̹����� �簢�� �׸���
        image->drawRectangle(w, h, rectWidth, rectHeight, drawBorder,On);

        // ������ �̹��� ����
        std::string modifiedFilename = imagePath.substr(0, imagePath.find_last_of('.')) + "_modified." + extension;
        if (image->saveImage(modifiedFilename)) {
            std::cout << "������ �̹��� ������ �Ϸ�Ǿ����ϴ�." << std::endl;
        }
        else {
            std::cout << "�̹��� ���� ����" << std::endl;
        }
        delete image;
    }
    else {
        std::cout << "�̹��� �ҷ����� ����" << std::endl;
        delete image;
    }
}


