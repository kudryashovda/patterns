#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class FlyBehavior {
public:
    virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior {
public:
    void fly() override {
        cout << "I'm flying!!!\n";
    }
};

class FlyNoWay : public FlyBehavior {
public:
    void fly() override {
        cout << "I can't fly\n";
    }
};

class FlyRocketPowered : public FlyBehavior {
public:
    void fly() override {
        cout << "I’m flying with a rocket!\n";
    }
};

class QuackBehavior {
public:
    virtual void quack() = 0;
};

class Quack : public QuackBehavior {
public:
    void quack() override {
        cout << "Quack!!!\n";
    }
};

class MuteQuack : public QuackBehavior {
public:
    void quack() override {
        cout << "<< Silence >>\n";
    }
};

class Squeak : public QuackBehavior {
public:
    void quack() override {
        cout << "Squeak\n";
    }
};

class Duck {
public:
    Duck(string name, FlyBehavior* flyBehavior, QuackBehavior* quackBehavior)
        : name_(move(name))
        , flyBehavior_(flyBehavior)
        , quackBehavior_(quackBehavior) {
    }

    void getName() {
        cout << "I'm " << name_ << '\n';
    }

    void swim() {
        cout << "I'm swimming\n";
    };

    void performFly() {
        if (flyBehavior_) {
            flyBehavior_->fly();
        }
    }

    void performQuack() {
        if (quackBehavior_) {
            quackBehavior_->quack();
        }
    }

    virtual void display() = 0;

    void setFlyBehavior(FlyBehavior* fb) {
        flyBehavior_ = move(unique_ptr<FlyBehavior>(fb));
    }

private:
    string name_;
    unique_ptr<FlyBehavior> flyBehavior_;
    unique_ptr<QuackBehavior> quackBehavior_;
};

class RedheadDuck : public Duck {
public:
    RedheadDuck(string name)
        : Duck(move(name), new FlyWithWings(), new Quack()) {
    }

    void display() override {
        cout << "I'm a RedheadDuck\n";
    }
};

class MallardDuck : public Duck {
public:
    MallardDuck(string name)
        : Duck(move(name), new FlyWithWings(), new Quack()) {
    }

    void display() override {
        cout << "I'm a MallardDuck\n";
    }
};

class RubberDuck : public Duck {
public:
    RubberDuck(string name)
        : Duck(move(name), new FlyNoWay(), new Squeak()) {
    }

    void display() override {
        cout << "I'm a RubberDuck\n";
    }
};

class WoodDuck : public Duck {
public:
    WoodDuck(string name)
        : Duck(move(name), new FlyNoWay(), new MuteQuack()) {
    }

    void display() override {
        cout << "I'm a WoodDuck\n";
    }
};

int main() {
    vector<unique_ptr<Duck>> ducks;
    ducks.emplace_back(new RedheadDuck("Bob"s));
    ducks.emplace_back(new MallardDuck("Tom"s));
    ducks.emplace_back(new RubberDuck("Mark"s));
    ducks.emplace_back(new WoodDuck("Alice"s));

    unique_ptr<Duck> super_wood_duck(new WoodDuck("SuperDuck"s));
    super_wood_duck->setFlyBehavior(new FlyRocketPowered());
    ducks.emplace_back(move(super_wood_duck));

    for (const auto& duck : ducks) {
        duck->getName();
        duck->display();
        duck->swim();
        duck->performQuack();
        duck->performFly();
        cout << '\n';
    }

    return 0;
}