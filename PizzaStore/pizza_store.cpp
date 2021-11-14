#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Ingredients
class Dough {
public:
    Dough() {
        cout << "  Take Dough base" << '\n';
    }
};

class Sauce {
public:
    Sauce() {
        cout << "  Take Sauce base" << '\n';
    }
};

class Cheese {
public:
    Cheese() {
        cout << "  Take Cheese base" << '\n';
    }
};

class Veggie {
public:
    Veggie(const string& name) {
        cout << "  Adding " << name << '\n';
    };
};

class Pepperoni {
public:
    Pepperoni() {
        cout << "  Take Pepperoni base" << '\n';
    }
};

class Clams {
public:
    Clams() {
        cout << "  Take Clams base" << '\n';
    }
};

// Preparing ingredients
// NYStyle
class ThinCrustDough : public Dough {
public:
    ThinCrustDough() {
        cout << '\t' << "Preparing Thin Crust Dough" << '\n';
    }
};

class MarinaraSauce : public Sauce {
public:
    MarinaraSauce() {
        cout << '\t' << "Preparing Marinara Sauce" << '\n';
    }
};

class ReggianoChease : public Cheese {
public:
    ReggianoChease() {
        cout << '\t' << "Preparing Reggiano Chease" << '\n';
    }
};

class SlicedPepperoni : public Pepperoni {
public:
    SlicedPepperoni() {
        cout << '\t' << "Preparing Sliced Pepperoni" << '\n';
    }
};

class FreshClams : public Clams {
public:
    FreshClams() {
        cout << '\t' << "Preparing Fresh Clams" << '\n';
    }
};

// ChicagoStyle
class ThickCrustDough : public Dough {
public:
    ThickCrustDough() {
        cout << '\t' << "Preparing Thick Crust Dough" << '\n';
    }
};

class PlumTomatoSauce : public Sauce {
public:
    PlumTomatoSauce() {
        cout << '\t' << "Preparing Plum Tomato Sauce" << '\n';
    }
};

class MozzarellaCheese : public Cheese {
public:
    MozzarellaCheese() {
        cout << '\t' << "Preparing Mozzarella Cheese" << '\n';
    }
};

class FrozenClams : public Clams {
};

// It is an abstract factory
class PizzaIngredientFactory {
public:
    virtual unique_ptr<Dough> createDough() = 0;
    virtual unique_ptr<Sauce> createSauce() = 0;
    virtual unique_ptr<Cheese> createCheese() = 0;
    virtual vector<unique_ptr<Veggie>> createVeggies() = 0;
    virtual unique_ptr<Pepperoni> createPepperoni() = 0;
    virtual unique_ptr<Clams> createClams() = 0;
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory {
public:
    unique_ptr<Dough> createDough() override {
        cout << "creating Dough in NY Style" << '\n';
        return make_unique<ThinCrustDough>();
    };
    unique_ptr<Sauce> createSauce() override {
        cout << "creating Sauce in NY Style" << '\n';
        return make_unique<MarinaraSauce>();
    };
    unique_ptr<Cheese> createCheese() override {
        cout << "creating Cheese in NY Style" << '\n';
        return make_unique<ReggianoChease>();
    };
    vector<unique_ptr<Veggie>> createVeggies() override {
        cout << "creating Veggies in NY Style" << '\n';

        vector<unique_ptr<Veggie>> veggies;
        veggies.emplace_back(make_unique<Veggie>("garlic"));
        veggies.emplace_back(make_unique<Veggie>("onion"));
        veggies.emplace_back(make_unique<Veggie>("mushroom"));
        veggies.emplace_back(make_unique<Veggie>("red_pepper"));

        return veggies;
    };

    unique_ptr<Pepperoni> createPepperoni() override {
        cout << "creating Pepperoni in NY Style" << '\n';
        return make_unique<SlicedPepperoni>();
    };
    unique_ptr<Clams> createClams() override {
        cout << "creating Claims in NY Style" << '\n';
        return make_unique<FreshClams>();
    };
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory {
public:
    unique_ptr<Dough> createDough() override {
        cout << "creating Dough in Chicago Style" << '\n';
        return make_unique<ThickCrustDough>();
    };
    unique_ptr<Sauce> createSauce() override {
        cout << "creating Sauce in Chicago Style" << '\n';
        return make_unique<PlumTomatoSauce>();
    };
    unique_ptr<Cheese> createCheese() override {
        cout << "creating Cheese in Chicago Style" << '\n';
        return make_unique<MozzarellaCheese>();
    };
    vector<unique_ptr<Veggie>> createVeggies() override {
        cout << "creating Veggies in Chicago Style" << '\n';

        vector<unique_ptr<Veggie>> veggies;
        veggies.emplace_back(make_unique<Veggie>("black_olives"));
        veggies.emplace_back(make_unique<Veggie>("spinach"));
        veggies.emplace_back(make_unique<Veggie>("egg_plant"));

        return veggies;
    };

    unique_ptr<Pepperoni> createPepperoni() override {
        cout << "creating Pepperoni in Chicago Style" << '\n';
        return make_unique<SlicedPepperoni>();
    };
    unique_ptr<Clams> createClams() override {
        cout << "creating Clams in Chicago Style" << '\n';
        return make_unique<FrozenClams>();
    };
};

enum class PizzaType {
    cheese,
    greek,
    pepperoni,
    clam,
    veggie
};

class Pizza {
public:
    virtual void prepare() = 0;

    virtual void bake() {
        cout << "Bake for 25 minutes at 350" << '\n';
    };

    virtual void cut() {
        cout << "Cutting the pizza into diagonal slices" << '\n';
    };

    virtual void box() {
        cout << "Place pizza in official PizzaStore box" << '\n';
    };

    void setName(string name) {
        name_ = move(name);
    }

    string getName() {
        return name_;
    }

    string toString() {
        string out;
        return out;
    }

protected:
    string name_;
    unique_ptr<Dough> dough_;
    unique_ptr<Sauce> sauce_;
    vector<unique_ptr<Veggie>> veggies_;
    unique_ptr<Cheese> cheese_;
    unique_ptr<Pepperoni> pepperoni_;
    unique_ptr<Clams> clams_;
};

class CheesePizza : public Pizza {
public:
    CheesePizza(unique_ptr<PizzaIngredientFactory> pizzaIngredientFactory)
        : ingredientFactory_(move(pizzaIngredientFactory)) {
    }

    void prepare() override {
        cout << "Preparing " << name_ << '\n';
        dough_ = ingredientFactory_->createDough();
        sauce_ = ingredientFactory_->createSauce();
        cheese_ = ingredientFactory_->createCheese();
    }

private:
    unique_ptr<PizzaIngredientFactory> ingredientFactory_;
};

class ClamPizza : public Pizza {
public:
    ClamPizza(unique_ptr<PizzaIngredientFactory> pizzaIngredientFactory)
        : ingredientFactory_(move(pizzaIngredientFactory)) {
    }

    void prepare() override {
        cout << "Preparing " << name_ << '\n';
        dough_ = ingredientFactory_->createDough();
        sauce_ = ingredientFactory_->createSauce();
        cheese_ = ingredientFactory_->createCheese();
        clams_ = ingredientFactory_->createClams();
    }

private:
    unique_ptr<PizzaIngredientFactory> ingredientFactory_;
};

class VeggiePizza : public Pizza {
public:
    VeggiePizza(unique_ptr<PizzaIngredientFactory> pizzaIngredientFactory)
        : ingredientFactory_(move(pizzaIngredientFactory)) {
    }

    void prepare() override {
        cout << "Preparing " << name_ << '\n';
        dough_ = ingredientFactory_->createDough();
        veggies_ = ingredientFactory_->createVeggies();
    }

private:
    unique_ptr<PizzaIngredientFactory> ingredientFactory_;
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
        unique_ptr<PizzaIngredientFactory> ingredientFactory = make_unique<NYPizzaIngredientFactory>();

        switch (pizza_type) {
        case PizzaType::cheese:
            pizza = make_unique<CheesePizza>(move(ingredientFactory));
            pizza->setName("New York Style Cheese Pizza");
            break;
        case PizzaType::clam:
            pizza = make_unique<ClamPizza>(move(ingredientFactory));
            pizza->setName("New York Style Clam Pizza");
            break;
        case PizzaType::veggie:
            pizza = make_unique<VeggiePizza>(move(ingredientFactory));
            pizza->setName("New York Style Veggie Pizza");
            break;
        }
        return pizza;
    }
};

class ChicagoPizzaStore : public PizzaStore {
public:
    unique_ptr<Pizza> createPizza(PizzaType pizza_type) override {
        unique_ptr<Pizza> pizza;
        unique_ptr<PizzaIngredientFactory> ingredientFactory = make_unique<ChicagoPizzaIngredientFactory>();

        switch (pizza_type) {
        case PizzaType::cheese:
            pizza = make_unique<CheesePizza>(move(ingredientFactory));
            pizza->setName("Chicago Style Cheese Pizza");
            break;
        case PizzaType::clam:
            pizza = make_unique<ClamPizza>(move(ingredientFactory));
            pizza->setName("Chicago Style Clam Pizza");
            break;
        case PizzaType::veggie:
            pizza = make_unique<VeggiePizza>(move(ingredientFactory));
            pizza->setName("Chicago Style Veggie Pizza");
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

    unique_ptr<Pizza> pizza_3 = chicago_store->orderPizza(PizzaType::veggie);
    cout << "Mark ordered a " << pizza_3->getName() << '\n'
         << '\n';

    return 0;
}