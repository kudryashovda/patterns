#pragma once

#include <string>

using namespace std;

class Machine;

class State {
public:
    State(const string& name, Machine& machine) : machine_(machine), name_(name) {}
    virtual void action1() = 0;
    virtual void action2() = 0;
    virtual void action3() = 0;
    string getName() const{ return name_; };
    ~State() = default;
protected:
    Machine &machine_;
    const string name_;
};

class State1 : public State {
public:
    State1(Machine &machine) : State("State1", machine) {}
    void action1() override;
    void action2() override;
    void action3() override;
};

class State2 : public State {
public:
    State2(Machine &machine) : State("State2", machine) {}
    void action1() override;
    void action2() override;
    void action3() override;
};


class Machine {
public:
    Machine() { state_ = new State1(*this); }
    void action1();
    void action2();
    void action3();
    ~Machine() { if (state_) delete state_; }

    void setState(State *new_state);
private:
    State *state_{ nullptr };
};
