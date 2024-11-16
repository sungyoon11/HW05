#include <iostream>
#include <string>
using namespace std;

class UI {
    static int n;  // 사용자 입력을 받기 위한 변수
public:
    static void start();  // 프로그램 시작 메시지 출력
    static int menu();    // 메뉴 선택을 위한 입력 함수
    static int insert();  // 도형 삽입을 위한 입력 함수
    static int del();     // 도형 삭제를 위한 입력 함수
};

int UI::n = 0;

void UI::start() {
    cout << "그래픽 에디터입니다." << endl;  // 프로그램 시작 메시지
}

int UI::menu() {
    cout << "삽입:1, 삭제:2, 모두보기:3, 종료:4 >> ";  // 메뉴 옵션 출력
    cin >> n;  // 사용자가 입력한 값 받기
    return n;  // 입력 받은 값을 반환
}

int UI::insert() {
    cout << "선:1, 원:2, 사각형:3 >> ";  // 도형 선택 메뉴 출력
    cin >> n;  // 사용자가 선택한 도형을 입력받기
    return n;  // 선택한 도형 종류 반환
}

int UI::del() {
    cout << "삭제하고자 하는 도형의 인덱스 >> ";  // 삭제할 도형의 인덱스를 입력받기
    cin >> n;  // 삭제할 도형의 인덱스 입력 받기
    return n;  // 입력 받은 인덱스 반환
}

class GraphicEditor {
    int index;  // 도형의 인덱스
public:
    GraphicEditor(int i) { index = i; }  // 생성자: 도형의 인덱스를 초기화
    virtual ~GraphicEditor() {}  // 가상 소멸자: 파생 클래스에서 제대로 소멸될 수 있도록
    virtual void show() = 0;  // 도형을 출력하기 위한 순수 가상 함수
    int getIndex() { return index; }  // 도형의 인덱스를 반환
    void subIndex() { --index; }  // 도형 인덱스를 1 감소
};

class Line : public GraphicEditor {
public:
    Line(int index) : GraphicEditor(index) {}  // Line 생성자
    void show() { cout << getIndex() << ": Line" << endl; }  // Line 도형 출력
};

class Circle : public GraphicEditor {
public:
    Circle(int index) : GraphicEditor(index) {}  // Circle 생성자
    void show() { cout << getIndex() << ": Circle" << endl; }  // Circle 도형 출력
};

class Rect : public GraphicEditor {
public:
    Rect(int index) : GraphicEditor(index) {}  // Rect 생성자
    void show() { cout << getIndex() << ": Rectangle" << endl; }  // Rectangle 도형 출력
};

int main() {
    GraphicEditor* g[100];  // 최대 100개의 도형을 저장할 배열
    UI::start();  // 프로그램 시작 메시지 출력
    int index = 0;  // 도형의 인덱스 초기화

    for (;;) {
        int m = UI::menu();  // 메뉴 선택
        if (m == 1) {  // 삽입
            int n = UI::insert();  // 삽입할 도형 종류 선택
            if (n == 1) {  // 선
                Line* l = new Line(index);  // Line 객체 생성
                g[index] = l;  // 배열에 추가
                ++index;  // 인덱스 증가
            }
            else if (n == 2) {  // 원
                Circle* c = new Circle(index);  // Circle 객체 생성
                g[index] = c;  // 배열에 추가
                ++index;  // 인덱스 증가
            }
            else if (n == 3) {  // 사각형
                Rect* r = new Rect(index);  // Rect 객체 생성
                g[index] = r;  // 배열에 추가
                ++index;  // 인덱스 증가
            }
            else {
                cout << "입력 에러" << endl;  // 잘못된 입력
            }
        }
        else if (m == 2) {  // 삭제
            int n = UI::del();  // 삭제할 도형의 인덱스 입력받기
            if (n >= 0 && n < index) {  // 유효한 인덱스인지 확인
                delete g[n];  // 해당 인덱스의 도형 객체 메모리 해제
                for (int i = n; i < index - 1; ++i) {  // 삭제한 후 배열을 한 칸씩 당기기
                    g[i] = g[i + 1];  // 한 칸씩 앞당기고
                    g[i]->subIndex();  // 인덱스 수정
                }
                --index;  // 전체 도형 개수 감소
            }
            else {
                cout << "유효하지 않은 인덱스입니다." << endl;  // 잘못된 인덱스 입력
            }
        }
        else if (m == 3) {  // 모두 보기
            for (int i = 0; i < index; ++i)  // 모든 도형 출력
                g[i]->show();
        }
        else if (m == 4) {  // 종료
            for (int i = 0; i < index; ++i) {  // 남아 있는 모든 도형 객체 메모리 해제
                delete g[i];
            }
            break;  // 프로그램 종료
        }
        else {
            cout << "입력 에러" << endl;  // 잘못된 메뉴 입력
        }
    }
    return 0;  // 프로그램 종료
}
