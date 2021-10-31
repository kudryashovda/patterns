#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Duck {
public:
    Duck(string name)
        : name_(move(name)) {
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

    void fly() {
        cout << "I'm flying!!!\n";
    }

    virtual void display() = 0;

private:
    string name_;
};

class RedheadDuck : public Duck {
public:
    RedheadDuck(string name)
        : Duck(move(name)) {
    }

    void display() override {
        cout << "I'm a RedheadDuck\n";
    }
};

class MallardDuck : public Duck {
public:
    MallardDuck(string name)
        : Duck(move(name)) {
    }

    void display() override {
        cout << "I'm a MallardDuck\n";
    }
};

class RubberDuck : public Duck {
public:
    RubberDuck(string name)
        : Duck(move(name)) {
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
        duck->fly();
        cout << '\n';
    }

    return 0;
}