#include "state.h"
#include <iostream>

using namespace std;

void State1::action1() { cout << "State1:action1\n"; }
void State1::action2() { cout << "State1:action2\n"; machine_.setState(new State2(machine_)); }
void State1::action3() { cout << "State1:action3\n"; }

void State2::action1() { cout << "State2:action1\n"; }
void State2::action2() { cout << "State2:action2\n"; }
void State2::action3() { cout << "State2:action3\n"; machine_.setState(new State1(machine_)); }


void Machine::action1() { state_->action1(); }
void Machine::action2() { state_->action2(); }
void Machine::action3() { state_->action3(); }

void Machine::setState(State *new_state) {
    cout << state_->getName() << " changed to " << new_state->getName() << '\n';
    if (state_) { delete state_; }
    state_ = new_state;
}
