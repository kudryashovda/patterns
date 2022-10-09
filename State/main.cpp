#include "state.h"

int main() {
    Machine machine; // state1
    machine.action2(); // only in this state machine state changes to state2
    machine.action1(); // now it is in state2
    machine.action2(); // in state2 no state changes happens
    machine.action3(); // but this action can change state to state1
}