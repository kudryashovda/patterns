#include <iostream>
#include <memory>

using namespace std;

class Singleton {
public:
    static unique_ptr<Singleton> getInstance() {
        if (!instance) {
            instance = unique_ptr<Singleton>(new Singleton());
        }
        return move(instance);
    }
    int GetMagicNumber() {
        return 12345;
    }
private:
    Singleton() = default;
    static unique_ptr<Singleton> instance;
};

unique_ptr<Singleton> Singleton::instance = nullptr;

int main() {
    auto props = Singleton::getInstance();

    std::cout << props->GetMagicNumber() << '\n';

    return 0;
}