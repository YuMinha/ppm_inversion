#include "UserInterface.h"
#include "Image.h"

using namespace std;

int main() {
    string directory = "Image"; // �̹��� ������ �ִ� ���丮
    vector<string> imageList = {
        "cam.pgm",
        "airplane.pgm",
        "house.ppm",
        "tiffany.ppm",
        "tiffany2.ppm",
        "worf.ppm"
    };
    //���ϸ�_inverted : ������ ����
    //���ϸ�_modifird : �簢�� ����
    while (true) {
        printMenu();
        int operation = getUserChoice();

        if (operation == 1) {
            /*
            * pgm�϶� �ȼ��� �ϳ��� pixel����ü�� �ϸ� ���� ����
            *   ������ �������� �Լ����� ���Ǿ��� ���ؾ���
            * ���� ��ġ �ٸ� ������ �ٲٱ�
            */
            processImageInversion(directory, imageList);
            ClearConsole(2);
        }
        else if (operation == 2) {
            int sel = 0;
            cout << "�ɼ�1: �̹��� �� �簢�� �׸���\n"
                << "�ɼ� 2: ���ο� ppm���Ͽ� �簢���� �׸���\n"
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
                * ������� �Է��� �޾� �簢���� �׸� ppm���� Ȥ�� pgm ������ �����Ͽ� �����Ѵ�.
                * �̹����� ũ��(�ִ� 256x256)
                * �簢���� ũ��(�̹����� ũ�⸦ �Ѿ�� �ʵ����Ѵ�.)
                * �簢���� �׵θ��� �׸� ������ ���� ä�� �簢���� �׸� ������ ����
                * ���(pgm) or �÷�(ppm)
                * ����̶�� �簢���� ��� �Է�, �÷���� rgb�� �Է�
                * �÷� ���ÿ� �´� ���� ���� �� ����
                * �Ϸ� ���� ���
                */
            }
            else
            {
                cerr << "�߸��� �����Դϴ�.";
            }

            ClearConsole(2);
        }
        else if (operation == 3) {
            break;
        }
        else {
            cout << "�߸��� �����Դϴ�. �ٽ� �����ϼ���." << endl;
            Sleep(1000);
            system("cls");
        }
    }

    return 0;
}
