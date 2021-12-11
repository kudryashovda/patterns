#include <iostream>

using namespace std;

class Light {
public:
    void on() {
        cout << "Light is on\n";
    };
    void off() {
        cout << "Light is off\n";
    };
};

class Command {
public:
    virtual void execute() = 0;
};

class LightOnCommand : public Command {
public:
    LightOnCommand(Light* light) {
        light_ = light;
    }
    void execute() override {
        light_->on();
    }

private:
    Light* light_;
};

class SimpleRemoteControl {
public:
    void setCommand(Command* command) {
        slot_ = command;
    }
    void buttonWasPressed() {
        slot_->execute();
    }

private:
    Command* slot_ = nullptr;
};

int main() {
    SimpleRemoteControl remote;
    Light light;
    LightOnCommand lightOn(&light);

    remote.setCommand(&lightOn);
    remote.buttonWasPressed();

    return 0;
}