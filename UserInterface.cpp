#include "UserInterface.h"

void printMenu() {
    std::cout << "    <�÷� ���� ó��>" << std::endl;
    std::cout << " =====================" << std::endl;
    std::cout << "  1. �̹��� �����ϱ�" << std::endl;
    std::cout << "  2. �簢�� �׸���" << std::endl;
    std::cout << "  3. ���α׷� ����" << std::endl;
    std::cout << "  -> ";
}

//�������� �ٸ� ���� �Է����� �� ���ѹݺ�
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
            std::cerr << "������ �Է��ϼ���( ����� �ٽ� �Է����ּ��� )";
            std::cin.clear();
            //�Է� ���� ����
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            Sleep(1000);
            system("cls");
            printMenu();
            continue;
        }
    }
}

int selectImage(const std::vector<std::string>& imageList) {
    std::cout << "\n�̹����� �����ϼ��� (��ȣ �Է�): " << std::endl;

    for (int i = 0; i < imageList.size(); ++i) {
        std::cout << i + 1 << ". " << imageList[i] << std::endl;
    }

    int selectedIndex;
    std::cin >> selectedIndex;

    if (selectedIndex >= 1 && selectedIndex <= static_cast<int>(imageList.size())) {
        return selectedIndex - 1; // ����ڰ� ������ �̹����� �ε��� ��ȯ
    }
    else {
        std::cout << "��ȿ���� ���� �����Դϴ�." << std::endl;
        return -1;
    }
}

void ClearConsole(int sec) {
    std::cout <<"����� �޴� ȭ������ ���ư��ϴ�." << std::endl;
    std::cout << "---------------" << std::endl;
    for (int cur_sec = 0; cur_sec < sec + 1; cur_sec++) {
        std::cout << sec - cur_sec+1;
        if (cur_sec != sec)std::cout << ",";
        Sleep(500);
    }
    system("cls");
}