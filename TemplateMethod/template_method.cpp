#include <iostream>

using namespace std;

class CaffeineBeverage {
public:
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
    void boilWater() {
        cout << "Boiling water" << '\n';
    }
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
    void pourInCup() {
        cout << "Pouring into cup" << '\n';
    }
};

class Coffee : public CaffeineBeverage {
public:
    void brew() override {
        cout << "Dripping Coffee through" << '\n';
    }
    void addCondiments() override {
        cout << "Adding Sugar and Milk" << '\n';
    }
};

class Tea : public CaffeineBeverage {
public:
    void brew() override {
        cout << "Steering the tea" << '\n';
    }
    void addCondiments() override {
        cout << "Adding lemon" << '\n';
    }
};
int main() {

    cout << "Welcome to out cafeteria" << '\n';
    Tea tea;
    Coffee coffee;

    cout << "Preparing tea" << '\n';
    tea.prepareRecipe();
    cout << '\n';
    cout << "Preparing coffee" << '\n';
    coffee.prepareRecipe();

    return 0;
}