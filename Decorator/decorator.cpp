#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

class Beverage {
public:
    virtual string getDescription() {
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

class CondimentDecorator : public Beverage {
protected:
    unique_ptr<Beverage> beverage_;
};

class Milk : public CondimentDecorator {
public:
    Milk(unique_ptr<Beverage> beverage) {
        beverage_ = move(beverage);
    }

    string getDescription() override {
        return beverage_->getDescription() + string(", Milk");
    }

    float cost() override {
        return beverage_->cost() + 0.10f;
    }
};

class Mocha : public CondimentDecorator {
public:
    Mocha(unique_ptr<Beverage> beverage) {
        beverage_ = move(beverage);
    }

    string getDescription() override {
        return beverage_->getDescription() + string(", Mocha");
    }

    float cost() override {
        return beverage_->cost() + 0.20f;
    }
};

class Whip : public CondimentDecorator {
public:
    Whip(unique_ptr<Beverage> beverage) {
        beverage_ = move(beverage);
    }

    string getDescription() override {
        return beverage_->getDescription() + string(", Whip");
    }

    float cost() override {
        return beverage_->cost() + 0.10f;
    }
};

class Soy : public CondimentDecorator {
public:
    Soy(unique_ptr<Beverage> beverage) {
        beverage_ = move(beverage);
    }

    string getDescription() override {
        return beverage_->getDescription() + string(", Soy");
    }

    float cost() override {
        return beverage_->cost() + 0.15f;
    }
};

class Caramel : public CondimentDecorator {
public:
    Caramel(unique_ptr<Beverage> beverage) {
        beverage_ = move(beverage);
    }

    string getDescription() override {
        return beverage_->getDescription() + string(", Caramel");
    }

    float cost() override {
        return beverage_->cost() + 0.15f;
    }
};

#define M_MakeEspresso make_unique<Espresso>()
#define M_AddMocha(X) make_unique<Mocha>(X)
#define M_AddMilk(X) make_unique<Milk>(X)

int main() {
    vector<unique_ptr<Beverage>> orders;

    orders.push_back(make_unique<Espresso>());
    orders.push_back(make_unique<Decaf>());
    orders.push_back(make_unique<HouseBlend>());
    orders.push_back(make_unique<DarkRoast>());

    orders.push_back(make_unique<Milk>(make_unique<HouseBlend>()));
    orders.push_back(make_unique<Whip>(make_unique<Decaf>()));
    orders.push_back(make_unique<Mocha>(make_unique<HouseBlend>()));

    orders.push_back(make_unique<Milk>(make_unique<Mocha>(make_unique<Espresso>())));
    // or with macro
    orders.push_back(M_AddMilk(M_AddMocha(M_MakeEspresso)));

    for (const auto& beverage : orders) {
        cout << beverage->getDescription() << '\t' << beverage->cost() << '\n';
    }

    return 0;
}