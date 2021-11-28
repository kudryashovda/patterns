#include <iostream>

class Singleton {
public:
    static Singleton* getInstance() {
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }
    int GetMagicNumber() {
        return 12345;
    }
private:
    Singleton() = default;
    static Singleton* instance;
};

Singleton* Singleton::instance = nullptr;

int main() {
    auto* props = Singleton::getInstance();

    std::cout << props->GetMagicNumber() << '\n';

    delete props;

    return 0;
}