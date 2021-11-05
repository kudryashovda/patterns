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
    Beverage* beverage_ = nullptr;
};

class Milk : public CondimentDecorator {
public:
    Milk(Beverage* beverage) {
        beverage_ = beverage;
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
    Mocha(Beverage* beverage) {
        beverage_ = beverage;
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
    Whip(Beverage* beverage) {
        beverage_ = beverage;
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
    Soy(Beverage* beverage) {
        beverage_ = beverage;
    }

    string getDescription() override {
        return beverage_->getDescription() + string(", Soy");
    }

    float cost() override {
        return beverage_->cost() + 0.15f;
    }
};

int main() {
    vector<unique_ptr<Beverage>> orders;

    orders.push_back(make_unique<Espresso>());
    orders.push_back(make_unique<Decaf>());
    orders.push_back(make_unique<HouseBlend>());
    orders.push_back(make_unique<DarkRoast>());

    unique_ptr<Beverage> house_blend = make_unique<HouseBlend>();
    orders.push_back(make_unique<Milk>(house_blend.release()));

    house_blend = make_unique<HouseBlend>();
    orders.push_back(make_unique<Whip>(house_blend.release()));

    house_blend = make_unique<HouseBlend>();
    orders.push_back(make_unique<Mocha>(house_blend.release()));

    house_blend = make_unique<HouseBlend>();
    unique_ptr<Beverage> house_blend_w_mocha = make_unique<Mocha>(house_blend.release());
    orders.push_back(make_unique<Mocha>(house_blend_w_mocha.release()));

    for (const auto& beverage : orders) {
        cout << beverage->getDescription() << '\t' << beverage->cost() << '\n';
    }

    return 0;
}