#include <iostream>

using namespace std;

// less duplicated code

class CaffeineBeverage {
public:
    virtual void prepareRecipe() = 0;
    virtual void boilWater() {
        cout << "Boiling water" << '\n';
    }
    virtual void pourInCup() {
        cout << "Pouring into cup" << '\n';
    }
};

class Coffee : public CaffeineBeverage {
public:
    void prepareRecipe() override {
        boilWater();
        brewCoffeeGrinds();
        pourInCup();
        addSugarAndMilk();
    }

    void brewCoffeeGrinds() {
        cout << "Dripping Coffee through" << '\n';
    }

    void addSugarAndMilk() {
        cout << "Adding Sugar and Milk" << '\n';
    }
};

class Tea : public CaffeineBeverage {
public:
    void prepareRecipe() override {
        boilWater();
        steepTeaBag();
        pourInCup();
        addLemon();
    }

    void steepTeaBag() {
        cout << "Steering the tea" << '\n';
    }
    void addLemon() {
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