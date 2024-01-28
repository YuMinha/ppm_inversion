#include "UserInterface.h"
#include "Image.h"

using namespace std;

int main() {
    string directory = "Image"; // 이미지 파일이 있는 디렉토리
    vector<string> imageList = {
        "cam.pgm",
        "airplane.pgm",
        "house.ppm",
        "tiffany.ppm",
        "tiffany2.ppm",
        "worf.ppm"
    };
    //파일명_inverted : 반전된 파일
    //파일명_modifird : 사각형 파일
    while (true) {
        printMenu();
        int operation = getUserChoice();

        if (operation == 1) {
            /*
            * pgm일때 픽셀이 하나라 pixel구조체로 하면 사진 깨짐
            *   구조를 따로할지 함수에서 조건쓸지 정해야함
            * 저장 위치 다른 폴더로 바꾸기
            */
            processImageInversion(directory, imageList);
            ClearConsole(2);
        }
        else if (operation == 2) {
            int sel = 0;
            cout << "옵션1: 이미지 위 사각형 그리기\n"
                << "옵션 2: 새로운 ppm파일에 사각형을 그리기\n"
                << "-> ";
            cin >> sel;
            if (sel == 1)
            {
                drawRectangleOnSelectedImage(directory, imageList);
            }
            else if (sel == 2)
            {
                processRectangleDrawing();
                /*
                * 사용자의 입력을 받아 사각형을 그린 ppm파일 혹은 pgm 파일을 생성하여 저장한다.
                * 이미지의 크기(최대 256x256)
                * 사각형의 크기(이미지의 크기를 넘어서지 않도록한다.)
                * 사각형을 테두리만 그릴 것인지 안을 채운 사각형을 그릴 것인지 선택
                * 흑백(pgm) or 컬러(ppm)
                * 흑백이라면 사각형의 밝기 입력, 컬러라면 rgb값 입력
                * 컬러 선택에 맞는 파일 생성 후 저장
                * 완료 문구 출력
                */
            }
            else
            {
                cerr << "잘못된 선택입니다.";
            }

            ClearConsole(2);
        }
        else if (operation == 3) {
            break;
        }
        else {
            cout << "잘못된 선택입니다. 다시 선택하세요." << endl;
            Sleep(1000);
            system("cls");
        }
    }

    return 0;
}
