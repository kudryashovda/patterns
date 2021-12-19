#include <iostream>

using namespace std;

// A lot of duplicated code

class Coffee {
public:
    void prepareRecipe() {
        boilWater();
        brewCoffeeGrinds();
        pourInCup();
        addSugarAndMilk();
    }

    void boilWater() {
        cout << "Boiling water" << '\n';
    }
    void brewCoffeeGrinds() {
        cout << "Dripping Coffee through" << '\n';
    }
    void pourInCup() {
        cout << "Pouring into cup" << '\n';
    }
    void addSugarAndMilk() {
        cout << "Adding Sugar and Milk" << '\n';
    }
};

class Tea {
public:
    void prepareRecipe() {
        boilWater();
        steepTeaBag();
        pourInCup();
        addLemon();
    }

    void boilWater() {
        cout << "Boiling water" << '\n';
    }
    void steepTeaBag() {
        cout << "Steering the tea" << '\n';
    }
    void pourInCup() {
        cout << "Pouring into cup" << '\n';
    }
    void addLemon() {
        cout << "Pouring into cup" << '\n';
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