#include <functional>
#include <iostream>

using std::cout;
using std::function;

class Button {
public:
    void click() {
        if (func_) {
            func_();
        }
    }
    void bind(function<void()>&& func) {
        func_ = move(func);
    }

private:
    function<void()> func_ = nullptr;
};

void onBtn1Click() {
    cout << "btn1 was clicked\n";
}

void onBtn2Click() {
    cout << "btn2 was clicked\n";
}

int main() {

    Button btn1;
    Button btn2;
    Button btn3;

    btn1.bind(onBtn1Click);
    btn2.bind(onBtn2Click);
    btn3.bind([]() { cout << "btn3 was clicked\n"; });

    btn1.click();
    btn2.click();
    btn3.click();

    btn1.click();
    btn2.click();
    btn3.click();

    return 0;
}