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

//중복되는 이름의 파일 저장하는 함수
std::string handleDuplicateFileName(const std::string& baseName) {
    std::string newName = baseName;
    int count = 1;

    while (std::ifstream(newName)) {
        // 파일 이름 확장자를 분리
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
        std::cerr << "파일을 열 수 없습니다." << std::endl;
        return false;
    }

    input >> magicNumber >> width >> height >> maxColor;

    if (maxColor != 255) {
        std::cerr << "올바른 PPM 파일이 아닙니다." << std::endl;
        return false;
    }

    pixels.resize(width * height);

    input.ignore(); // 빈 칸 라인 무시
    input.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * sizeof(Pixel));

    return true;
}
bool PPMImage::saveImage(const std::string& inputfilename)
{
    std::string filename = handleDuplicateFileName(inputfilename);

    std::ofstream output(filename, std::ios::binary);
    if (!output) {
        std::cerr << "출력 파일을 열 수 없습니다." << std::endl;
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

    // 입력된 사각형 크기가 이미지 크기를 초과하면 크기를 조정
    rectWidth = min(rectWidth, width);
    rectHeight = min(rectHeight, height);

    // 이미지의 중심 좌표 계산
    int centerX = width / 2;
    int centerY = height / 2;

    // 사각형의 시작 좌표 계산 (중심 기준으로)
    int startX = centerX - rectWidth / 2;
    int startY = centerY - rectHeight / 2;
    ;
    pixels.resize(width * height);

    Pixel color;
    int r, g, b;
    std::cout << "테두리 or 사각형의 색상를 입력하세요(r, g, b 값) : ";
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
    // 사각형 그리기
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            index = y * width + x;
            Pixel& pixel = pixels[index];
            if (x >= startX && x < startX + rectWidth && y >= startY && y < startY + rectHeight) {
                // 사각형 내부 픽셀
                if (drawBorder) {
                    // 테두리만 그리는 경우
                    if (x == startX || x == startX + rectWidth - 1 || y == startY || y == startY + rectHeight - 1) {
                        // 테두리 픽셀
                        pixel.r = color.r;
                        pixel.g = color.g;
                        pixel.b = color.b;
                    }
                }
                else {
                    // 내부를 채우는 경우
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
        std::cerr << "파일을 열 수 없습니다." << std::endl;
        return false;
    }

    input >> magicNumber >> width >> height >> maxColor;

    if (maxColor != 255) {
        std::cerr << "올바른 이미지 파일이 아닙니다." << std::endl;
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
    * 반복해서 같은 거 저장하면 덮어짐
    * 중복된 이름 처리 필요
    */
    std::string filename = handleDuplicateFileName(inputfilename);
    std::ofstream output(filename, std::ios::binary);
    if (!output) {
        std::cerr << "출력 파일을 열 수 없습니다." << std::endl;
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

    // 입력된 사각형 크기가 이미지 크기를 초과하면 크기를 조정
    rectWidth = min(rectWidth, width);
    rectHeight = min(rectHeight, height);

    // 이미지의 중심 좌표 계산
    int centerX = width / 2;
    int centerY = height / 2;

    // 사각형의 시작 좌표 계산 (중심 기준으로)
    int startX = centerX - rectWidth / 2;
    int startY = centerY - rectHeight / 2;
    ;
    pixels.resize(width * height);

    int br;
    std::cout << "테두리 or 사각형의 밝기를 입력하세요(0~255 : 클 수록 밝음) : ";
    std::cin >> br;
    
    if (!On)
    {
        for (auto& pixel : pixels)
        {
            pixel.gray = 255 - br;
        }
    }

    int index = 0;
    // 사각형 그리기
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            index = y * width + x;
            Pixel& pixel = pixels[index];
            if (x >= startX && x < startX + rectWidth && y >= startY && y < startY + rectHeight) {
                // 사각형 내부 픽셀
                if (drawBorder) {
                    // 테두리만 그리는 경우
                    if (x == startX || x == startX + rectWidth - 1 || y == startY || y == startY + rectHeight - 1) {
                        // 테두리 픽셀
                        pixel.gray = br;
                    }
                }
                else {
                    // 내부를 채우는 경우
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

    // 이미지 확장자를 분석하여 PPM 또는 PGM 클래스를 선택
    std::string extension = imagePath.substr(imagePath.find_last_of('.') + 1);
    Image* image;
    if (extension == "ppm") {
        image = new PPMImage();
    }
    else if (extension == "pgm") {
        image = new PGMImage();
    }
    else {
        std::cout << "지원하지 않는 이미지 형식입니다." << std::endl;
        return;
    }

    if (image->loadImage(imagePath)) {
        image->invert();
        std::string invertedFilename = imagePath.substr(0, imagePath.find_last_of('.')) + "_inverted." + extension;
        if (image->saveImage(invertedFilename)) {
            std::cout << "이미지 저장이 완료되었습니다." << std::endl;
        }
        else {
            std::cout << "이미지 저장 실패" << std::endl;
        }
        delete image;
    }
    else {
        std::cout << "이미지 불러오기 실패" << std::endl;
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

    std::cout << "파일 형식을 지정해주세요 (1: 컬러 이미지, 0 : 흑백 이미지) : ";

    if (!(std::cin >> isColor)) {
        std::cerr << "올바르지 않은 입력입니다. 숫자 0 또는 1을 입력해주세요." << std::endl;
        std::cin.clear(); // 스트림의 오류 플래그 초기화
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // 입력 버퍼 비우기
        return; // 프로그램 종료 또는 오류 처리
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
        std::cerr << "올바르지 않은 형식입니다. 0혹은 1을 입력해주세요.";
        return ;
    }

    std::cout << "이미지 너비를 입력하세요 (최대 255): ";
    std::cin >> imageWidth;
    std::cout << "이미지 높이를 입력하세요 (최대 255): ";
    std::cin >>imageHeight;

    if (imageWidth > 256 || imageHeight > 256)
    {
        std::cerr << "이미지의 크기가 너무 큽니다.\n";
        return;
    }

    std::cout << "사각형 너비를 입력하세요: ";
    std::cin >> rectWidth;
    std::cout << "사각형 높이를 입력하세요: ";
    std::cin >> rectHeight;

    if (rectWidth > imageWidth || rectHeight > imageHeight) {
        std::cerr << "사각형의 크기가 너무 큽니다.\n";
        return;
    }

    std::cout << "사각형 형태를 지정해 주세요 (1: 테두리만, 0: 내부 채우기): ";
    std::cin >> drawBorder;

    image->initialize(imageWidth, imageHeight);

    image->drawRectangle(imageWidth, imageHeight, rectWidth, rectHeight, drawBorder,On);
    // 이미지 저장
    std::string invertedFilename = file + extention;
    if (image->saveImage(invertedFilename)) {
        std::cout << "이미지 저장이 완료되었습니다." << std::endl;
    }
    else {
        std::cout << "이미지 저장 실패" << std::endl;
    }
    delete image;
}
void drawRectangleOnSelectedImage(const std::string& directory, const std::vector<std::string>& imageList) {
    bool On = true;
    int selectedIndex = selectImage(imageList);
    if (selectedIndex == -1) return;
    std::string imagePath = directory + "/" + imageList[selectedIndex];

    // 이미지 확장자를 분석하여 PPM 또는 PGM 클래스를 선택
    std::string extension = imagePath.substr(imagePath.find_last_of('.') + 1);
    Image* image;
    if (extension == "ppm") {
        image = new PPMImage();
    }
    else if (extension == "pgm") {
        image = new PGMImage();
    }
    else {
        std::cout << "지원하지 않는 이미지 형식입니다." << std::endl;
        return;
    }

    if (image->loadImage(imagePath)) {
        // 사용자로부터 사각형 정보 입력 받기
        int rectWidth, rectHeight;
        bool drawBorder;
        int w, h;
        w = image->GetWidth();
        h = image->Getheight();
        std::cout << "사각형 너비와 높이를 입력하세요 (최대 " << w<< "x" << h << "): ";
        std::cin >> rectWidth >> rectHeight;

        if (rectWidth > w || rectHeight > h) {
            std::cerr << "사각형의 크기가 이미지를 초과합니다." << std::endl;
            delete image;
            return;
        }

        std::cout << "사각형 형태를 지정해 주세요 (1: 테두리만, 0: 내부 채우기): ";
        std::cin >> drawBorder;

        // 이미지에 사각형 그리기
        image->drawRectangle(w, h, rectWidth, rectHeight, drawBorder,On);

        // 수정된 이미지 저장
        std::string modifiedFilename = imagePath.substr(0, imagePath.find_last_of('.')) + "_modified." + extension;
        if (image->saveImage(modifiedFilename)) {
            std::cout << "수정된 이미지 저장이 완료되었습니다." << std::endl;
        }
        else {
            std::cout << "이미지 저장 실패" << std::endl;
        }
        delete image;
    }
    else {
        std::cout << "이미지 불러오기 실패" << std::endl;
        delete image;
    }
}


