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

class SimplePizzaFactory {
public:
    unique_ptr<Pizza> createPizza(PizzaType pizza_type) {
        unique_ptr<Pizza> pizza;

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
        }

        return pizza;
    }
};

// Problem:
// nyStore -> NYPizzaFactory
// chicagoStore -> ChicagoPizzaFactory

// every store has it own sequence of pizza recipe

class PizzaStore {
public:
    PizzaStore(SimplePizzaFactory* factory)
        : factory_(factory) {
    }

    unique_ptr<Pizza> orderPizza(PizzaType pizza_type) {
        unique_ptr<Pizza> pizza = factory_->createPizza(pizza_type);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }

private:
    SimplePizzaFactory* factory_;
};

int main() {
    SimplePizzaFactory factory;

    PizzaStore pizza_store(&factory);

    const auto pizza = pizza_store.orderPizza(PizzaType::pepperoni);

    return 0;
}