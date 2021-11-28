#include <iostream>

using namespace std;

class Singleton {
public:
    static Singleton *getInstance() {
        static Singleton instance;
        return &instance;
    }
    int GetMagicNumber() const {
        return magic_number;
    }

    void SetMagicNumber(int num) {
        magic_number = num;
    }
private:
    Singleton() = default;
    int magic_number = 0;
};

int main() {
    auto *props = Singleton::getInstance();
    auto *props2 = Singleton::getInstance();

    props2->SetMagicNumber(555);

    std::cout << props->GetMagicNumber() << '\n';

    return 0;
}