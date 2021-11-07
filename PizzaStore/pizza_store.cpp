#include <iostream>
#include <memory>

using std::make_unique;
using std::unique_ptr;

enum class PizzaType {
    cheese,
    greek,
    pepperoni
};

class Pizza {
public:
    virtual void prepare() = 0;
    void bake(){};
    void cut(){};
    void box(){};
};

class CheesePizza : public Pizza {
public:
    void prepare() override{};
};

class GreekPizza : public Pizza {
public:
    void prepare() override{};
};

class PepperoniPizza : public Pizza {
public:
    void prepare() override{};
};

unique_ptr<Pizza> orderPizza(PizzaType pizza_type) {
    unique_ptr<Pizza> pizza;

    // this is a problem - if you wish to add or remove some pizza types - you'll have to change this code
    switch (pizza_type) {
    case PizzaType::cheese:
        pizza = make_unique<CheesePizza>();
        break;
    case PizzaType::greek:
        pizza = make_unique<GreekPizza>();
        break;
    case PizzaType::pepperoni:
        pizza = make_unique<PepperoniPizza>();
        break;
    default:
        return pizza; // nullptr
    }

    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();

    return pizza;
}

int main() {
    auto order = orderPizza(PizzaType::cheese);
    if (!order) {
        return -1;
    }

    return 0;
}