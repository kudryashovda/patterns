#include <iostream>
#include <vector>

using namespace std;

class Light {
public:
    Light(string location) {
        location_ = move(location);
    }
    void on() {
        cout << location_ << " light is on\n";
    };
    void off() {
        cout << location_ << " light is off\n";
    };

private:
    string location_;
};

class Stereo {
public:
    Stereo(string location) {
        location_ = move(location);
    }
    void on() {
        cout << location_ << " stereo is on\n";
    };
    void off() {
        cout << location_ << " stereo is off\n";
    };
    void setCD() {
        input_type_ = "CD";
        cout << location_ << " stereo is set for CD input\n";
    }
    void setVolume(int volume) {
        volume_ = volume;
        cout << location_ << " stereo volume set to " << volume_ << '\n';
    }

private:
    string location_;
    string input_type_ = "undefined";
    int volume_ = 0;
};

class Command {
public:
    virtual void execute() = 0;
    virtual string getName() = 0;
};

class NoCommand : public Command {
public:
    void execute() override {
    }
    string getName() override {
        return "NoCommand";
    }
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

class StereoOnWithCDCommand : public Command {
public:
    StereoOnWithCDCommand(Stereo* stereo) {
        stereo_ = stereo;
    }
    void execute() override {
        stereo_->on();
        stereo_->setCD();
        stereo_->setVolume(11);
    }
    string getName() override {
        return "StereoOnWithCDCommand";
    }

private:
    Stereo* stereo_;
};

class StereoOffCommand : public Command {
public:
    StereoOffCommand(Stereo* stereo) {
        stereo_ = stereo;
    }
    void execute() override {
        stereo_->off();
    }
    string getName() override {
        return "StereoOffCommand";
    }

private:
    Stereo* stereo_;
};

class RemoteControl {
public:
    RemoteControl() {
        constexpr int programs_count = 7;
        for (int i = 0; i < programs_count; ++i) {
            onCommands_.push_back(&no_command_);
            offCommands_.push_back(&no_command_);
        }
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
    void printCommands() {
        cout << "\n------ Remote Control ------\n";
        for (int i = 0; i < onCommands_.size(); ++i) {
            cout << "[slot " << i << "] " << onCommands_[i]->getName() << '\t' << offCommands_[i]->getName() << "\n";
        }
    }

private:
    vector<Command*> onCommands_;
    vector<Command*> offCommands_;
    NoCommand no_command_;
};

int main() {
    RemoteControl remote;

    Light livingRoomLight("Living Room");
    LightOnCommand livingRoomLightOn(&livingRoomLight);
    LightOffCommand livingRoomLightOff(&livingRoomLight);

    Stereo stereo("Living Room");
    StereoOnWithCDCommand stereoOnWithCdCommand(&stereo);
    StereoOffCommand stereoOffCommand(&stereo);

    remote.setCommand(0, &livingRoomLightOn, &livingRoomLightOff);
    remote.setCommand(3, &stereoOnWithCdCommand, &stereoOffCommand);

    remote.printCommands();

    remote.onButtonWasPressed(0);
    remote.offButtonWasPressed(0);
    remote.onButtonWasPressed(3);
    remote.offButtonWasPressed(3);

    return 0;
}
