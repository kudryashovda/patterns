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

class Duck {
public:
    Duck(string name, FlyBehavior* flyBehavior)
        : name_(move(name))
        , flyBehavior_(flyBehavior) {
    }

    void getName() {
        cout << "I'm " << name_ << '\n';
    }

    void quack() {
        cout << "QwaQwa\n";
    };

    void swim() {
        cout << "I'm swimming\n";
    };

    void performFly() {
        if (flyBehavior_) {
            flyBehavior_->fly();
        }
    }

    virtual void display() = 0;

private:
    string name_;
    unique_ptr<FlyBehavior> flyBehavior_;
};

class RedheadDuck : public Duck {
public:
    RedheadDuck(string name)
        : Duck(move(name), new FlyWithWings()) {
    }

    void display() override {
        cout << "I'm a RedheadDuck\n";
    }
};

class MallardDuck : public Duck {
public:
    MallardDuck(string name)
        : Duck(move(name), new FlyWithWings()) {
    }

    void display() override {
        cout << "I'm a MallardDuck\n";
    }
};

class RubberDuck : public Duck {
public:
    RubberDuck(string name)
        : Duck(move(name), new FlyNoWay()) {
    }

    void display() override {
        cout << "I'm a RubberDuck\n";
    }
};

int main() {
    vector<unique_ptr<Duck>> ducks;
    ducks.emplace_back(new RedheadDuck("Bob"s));
    ducks.emplace_back(new RedheadDuck("Justin"s));

    ducks.emplace_back(new MallardDuck("Tom"s));
    ducks.emplace_back(new MallardDuck("Anton"s));

    ducks.emplace_back(new RubberDuck("Mark"s));
    ducks.emplace_back(new RubberDuck("Jason"s));

    for (const auto& duck : ducks) {
        duck->getName();
        duck->display();
        duck->swim();
        duck->quack();
        duck->performFly();
        cout << '\n';
    }

    return 0;
}