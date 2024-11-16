#include <iostream>
#include <string>
using namespace std;

class UI {
    static int n;  // ����� �Է��� �ޱ� ���� ����
public:
    static void start();  // ���α׷� ���� �޽��� ���
    static int menu();    // �޴� ������ ���� �Է� �Լ�
    static int insert();  // ���� ������ ���� �Է� �Լ�
    static int del();     // ���� ������ ���� �Է� �Լ�
};

int UI::n = 0;

void UI::start() {
    cout << "�׷��� �������Դϴ�." << endl;  // ���α׷� ���� �޽���
}

int UI::menu() {
    cout << "����:1, ����:2, ��κ���:3, ����:4 >> ";  // �޴� �ɼ� ���
    cin >> n;  // ����ڰ� �Է��� �� �ޱ�
    return n;  // �Է� ���� ���� ��ȯ
}

int UI::insert() {
    cout << "��:1, ��:2, �簢��:3 >> ";  // ���� ���� �޴� ���
    cin >> n;  // ����ڰ� ������ ������ �Է¹ޱ�
    return n;  // ������ ���� ���� ��ȯ
}

int UI::del() {
    cout << "�����ϰ��� �ϴ� ������ �ε��� >> ";  // ������ ������ �ε����� �Է¹ޱ�
    cin >> n;  // ������ ������ �ε��� �Է� �ޱ�
    return n;  // �Է� ���� �ε��� ��ȯ
}

class GraphicEditor {
    int index;  // ������ �ε���
public:
    GraphicEditor(int i) { index = i; }  // ������: ������ �ε����� �ʱ�ȭ
    virtual ~GraphicEditor() {}  // ���� �Ҹ���: �Ļ� Ŭ�������� ����� �Ҹ�� �� �ֵ���
    virtual void show() = 0;  // ������ ����ϱ� ���� ���� ���� �Լ�
    int getIndex() { return index; }  // ������ �ε����� ��ȯ
    void subIndex() { --index; }  // ���� �ε����� 1 ����
};

class Line : public GraphicEditor {
public:
    Line(int index) : GraphicEditor(index) {}  // Line ������
    void show() { cout << getIndex() << ": Line" << endl; }  // Line ���� ���
};

class Circle : public GraphicEditor {
public:
    Circle(int index) : GraphicEditor(index) {}  // Circle ������
    void show() { cout << getIndex() << ": Circle" << endl; }  // Circle ���� ���
};

class Rect : public GraphicEditor {
public:
    Rect(int index) : GraphicEditor(index) {}  // Rect ������
    void show() { cout << getIndex() << ": Rectangle" << endl; }  // Rectangle ���� ���
};

int main() {
    GraphicEditor* g[100];  // �ִ� 100���� ������ ������ �迭
    UI::start();  // ���α׷� ���� �޽��� ���
    int index = 0;  // ������ �ε��� �ʱ�ȭ

    for (;;) {
        int m = UI::menu();  // �޴� ����
        if (m == 1) {  // ����
            int n = UI::insert();  // ������ ���� ���� ����
            if (n == 1) {  // ��
                Line* l = new Line(index);  // Line ��ü ����
                g[index] = l;  // �迭�� �߰�
                ++index;  // �ε��� ����
            }
            else if (n == 2) {  // ��
                Circle* c = new Circle(index);  // Circle ��ü ����
                g[index] = c;  // �迭�� �߰�
                ++index;  // �ε��� ����
            }
            else if (n == 3) {  // �簢��
                Rect* r = new Rect(index);  // Rect ��ü ����
                g[index] = r;  // �迭�� �߰�
                ++index;  // �ε��� ����
            }
            else {
                cout << "�Է� ����" << endl;  // �߸��� �Է�
            }
        }
        else if (m == 2) {  // ����
            int n = UI::del();  // ������ ������ �ε��� �Է¹ޱ�
            if (n >= 0 && n < index) {  // ��ȿ�� �ε������� Ȯ��
                delete g[n];  // �ش� �ε����� ���� ��ü �޸� ����
                for (int i = n; i < index - 1; ++i) {  // ������ �� �迭�� �� ĭ�� ����
                    g[i] = g[i + 1];  // �� ĭ�� �մ���
                    g[i]->subIndex();  // �ε��� ����
                }
                --index;  // ��ü ���� ���� ����
            }
            else {
                cout << "��ȿ���� ���� �ε����Դϴ�." << endl;  // �߸��� �ε��� �Է�
            }
        }
        else if (m == 3) {  // ��� ����
            for (int i = 0; i < index; ++i)  // ��� ���� ���
                g[i]->show();
        }
        else if (m == 4) {  // ����
            for (int i = 0; i < index; ++i) {  // ���� �ִ� ��� ���� ��ü �޸� ����
                delete g[i];
            }
            break;  // ���α׷� ����
        }
        else {
            cout << "�Է� ����" << endl;  // �߸��� �޴� �Է�
        }
    }
    return 0;  // ���α׷� ����
}
