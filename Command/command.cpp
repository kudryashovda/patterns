#include <iostream>
#include <sstream>
#include <vector>

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
    virtual string getName() = 0;
};

class LightOnCommand : public Command {
public:
    LightOnCommand(Light* light) {
        light_ = light;
    }
    void execute() override {
        light_->on();
    }
    string getName() override {
        return "LightOnCommand";
    }

private:
    Light* light_;
};

class LightOffCommand : public Command {
public:
    LightOffCommand(Light* light) {
        light_ = light;
    }
    void execute() override {
        light_->off();
    }
    string getName() override {
        return "LightOffCommand";
    }

private:
    Light* light_;
};

class RemoteControl {
public:
    RemoteControl() {
        constexpr int programs_count = 1;
        onCommands_.resize(programs_count);
        offCommands_.resize(programs_count);
    }

    void setCommand(int slot, Command* onCommand, Command* offCommand) {
        onCommands_[slot] = onCommand;
        offCommands_[slot] = offCommand;
    }
    void onButtonWasPressed(int slot) {
        onCommands_.at(slot)->execute();
    }
    void offButtonWasPressed(int slot) {
        offCommands_.at(slot)->execute();
    }
    string toString() {
        stringstream ss;
        ss << "\n------ Remote Control ------\n";
        for (int i = 0; i < onCommands_.size(); ++i) {
            ss << "[slot " << i << "] " << onCommands_[i]->getName() << "    " << offCommands_[i]->getName() << "\n";
        }

        return ss.str();
    }

private:
    vector<Command*> onCommands_;
    vector<Command*> offCommands_;
};

int main() {
    RemoteControl remote;
    Light light;
    LightOnCommand lightOn(&light);
    LightOffCommand lightOff(&light);

    remote.setCommand(0, &lightOn, &lightOff);

    remote.onButtonWasPressed(0);
    remote.offButtonWasPressed(0);
    cout << remote.toString();

    return 0;
}
