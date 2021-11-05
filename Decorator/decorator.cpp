#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::vector;

class Beverage {
public:
    string getDescription() {
        return description_;
    }

    virtual float cost() = 0;
    virtual ~Beverage() = default;

protected:
    string description_;
};

class HouseBlend : public Beverage {
public:
    HouseBlend() {
        description_ = "HouseBlend";
    }
    float cost() override {
        return 0.89;
    }
};

class DarkRoast : public Beverage {
public:
    DarkRoast() {
        description_ = "DarkRoast";
    }
    float cost() override {
        return 0.99;
    }
};

class Decaf : public Beverage {
public:
    Decaf() {
        description_ = "Decaf";
    }
    float cost() override {
        return 1.05;
    }
};

class Espresso : public Beverage {
public:
    Espresso() {
        description_ = "Espresso";
    }
    float cost() override {
        return 1.99;
    }
};

int main() {
    vector<unique_ptr<Beverage>> orders;

    orders.push_back(make_unique<Espresso>());
    orders.push_back(make_unique<Decaf>());
    orders.push_back(make_unique<HouseBlend>());
    orders.push_back(make_unique<DarkRoast>());

    for (const auto& beverage : orders) {
        cout << beverage->getDescription() << '\t' << beverage->cost() << '\n';
    }

    return 0;
}