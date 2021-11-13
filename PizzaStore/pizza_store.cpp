#include <iostream>
#include <memory>
#include <vector>

using namespace std;

enum class PizzaType {
    cheese,
    greek,
    pepperoni
};

class Pizza {
public:
    virtual void prepare() {
        cout << "Preparing " << name_ << '\n';
        cout << "Tossing dough " << dough_ << '\n';
        cout << "Adding sauce " << sauce_ << '\n';

        cout << "Adding toppings " << '\n';
        for (const auto& topping : toppings_) {
            cout << "    " << topping;
        }
        cout << '\n';
    };

    virtual void bake() {
        cout << "Bake for 25 minutes at 350" << '\n';
    };

    virtual void cut() {
        cout << "Cutting the pizza into diagonal slices" << '\n';
    };

    virtual void box() {
        cout << "Place pizza in official PizzaStore box" << '\n';
    };

    string getName() {
        return name_;
    }

protected:
    string name_;
    string dough_;
    string sauce_;
    vector<string> toppings_;
};

class NYStyleCheesePizza : public Pizza {
public:
    NYStyleCheesePizza() {
        name_ = "NY Style Sauce and Cheese Pizza";
        dough_ = "Thin Crust Dough";
        sauce_ = "Marinara Sauce";

        toppings_.emplace_back("Grated Reggiano Cheese");
    }
};

class ChicagoStyleCheesePizza : public Pizza {
public:
    ChicagoStyleCheesePizza() {
        name_ = "Chicago Style Deep Dish Cheese Pizza";
        dough_ = "Extra Thick Crust Dough";
        sauce_ = "Plum Tomato Sauce";

        toppings_.emplace_back("Shredded Mozzarella Cheese");
    }
    void cut() override {
        cout << "Cutting the pizza into square slices" << '\n';
    }
};

class NYStyleGreekPizza : public Pizza {
};

class ChicagoStyleGreekPizza : public Pizza {
};

class NYStylePepperoniPizza : public Pizza {
};

class ChicagoStylePepperoniPizza : public Pizza {
};

class PizzaStore {
public:
    unique_ptr<Pizza> orderPizza(PizzaType pizza_type) {
        unique_ptr<Pizza> pizza = createPizza(pizza_type);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }

protected:
    virtual unique_ptr<Pizza> createPizza(PizzaType pizza_type) = 0;
};

class NYPizzaStore : public PizzaStore {
public:
    unique_ptr<Pizza> createPizza(PizzaType pizza_type) override {
        unique_ptr<Pizza> pizza;

        switch (pizza_type) {
        case PizzaType::cheese:
            pizza = make_unique<NYStyleCheesePizza>();
            break;
        case PizzaType::greek:
            pizza = make_unique<NYStyleGreekPizza>();
            break;
        case PizzaType::pepperoni:
            pizza = make_unique<NYStylePepperoniPizza>();
            break;
        }

        return pizza;
    }
};

class ChicagoPizzaStore : public PizzaStore {
public:
    unique_ptr<Pizza> createPizza(PizzaType pizza_type) override {
        unique_ptr<Pizza> pizza;

        switch (pizza_type) {
        case PizzaType::cheese:
            pizza = make_unique<ChicagoStyleCheesePizza>();
            break;
        case PizzaType::greek:
            pizza = make_unique<ChicagoStyleGreekPizza>();
            break;
        case PizzaType::pepperoni:
            pizza = make_unique<ChicagoStylePepperoniPizza>();
            break;
        }

        return pizza;
    }
};

int main() {
    unique_ptr<PizzaStore> ny_store(new NYPizzaStore);
    unique_ptr<PizzaStore> chicago_store(new ChicagoPizzaStore);

    unique_ptr<Pizza> pizza_1 = ny_store->orderPizza(PizzaType::cheese);
    cout << "Ethan ordered a " << pizza_1->getName() << '\n'
         << '\n';

    unique_ptr<Pizza> pizza_2 = chicago_store->orderPizza(PizzaType::cheese);
    cout << "Joel ordered a " << pizza_2->getName() << '\n'
         << '\n';

    return 0;
}