#include "UserInterface.h"

void printMenu() {
    std::cout << "    <컬러 영상 처리>" << std::endl;
    std::cout << " =====================" << std::endl;
    std::cout << "  1. 이미지 반전하기" << std::endl;
    std::cout << "  2. 사각형 그리기" << std::endl;
    std::cout << "  3. 프로그램 종료" << std::endl;
    std::cout << "  -> ";
}

//정수말고 다른 형을 입력했을 때 무한반복
int getUserChoice() {
    int choice;
    while (true)
    {
        if (std::cin >> choice)
        {
            return choice;
        }
        else
        {
            std::cerr << "정수만 입력하세요( 잠시후 다시 입력해주세요 )";
            std::cin.clear();
            //입력 버퍼 비우기
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            Sleep(1000);
            system("cls");
            printMenu();
            continue;
        }
    }
}

int selectImage(const std::vector<std::string>& imageList) {
    std::cout << "\n이미지를 선택하세요 (번호 입력): " << std::endl;

    for (int i = 0; i < imageList.size(); ++i) {
        std::cout << i + 1 << ". " << imageList[i] << std::endl;
    }

    int selectedIndex;
    std::cin >> selectedIndex;

    if (selectedIndex >= 1 && selectedIndex <= static_cast<int>(imageList.size())) {
        return selectedIndex - 1; // 사용자가 선택한 이미지의 인덱스 반환
    }
    else {
        std::cout << "유효하지 않은 선택입니다." << std::endl;
        return -1;
    }
}

void ClearConsole(int sec) {
    std::cout <<"잠시후 메뉴 화면으로 돌아갑니다." << std::endl;
    std::cout << "---------------" << std::endl;
    for (int cur_sec = 0; cur_sec < sec + 1; cur_sec++) {
        std::cout << sec - cur_sec+1;
        if (cur_sec != sec)std::cout << ",";
        Sleep(500);
    }
    system("cls");
}