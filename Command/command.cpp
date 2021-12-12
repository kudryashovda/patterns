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
    virtual void undo() = 0;
    virtual string getName() = 0;
};

class NoCommand : public Command {
public:
    void execute() override {
    }
    void undo() override {
    }
    string getName() override {
        return "NoCommand";
    }
};

class MacroCommand : public Command {
public:
    MacroCommand(vector<Command*> commands) {
        commands_ = move(commands);
    }
    void execute() override {
        for (const auto& command : commands_) {
            command->execute();
        }
    }
    void undo() override {
        for (const auto& command : commands_) {
            command->undo();
        }
    }
    string getName() override {
        return "MacroCommand";
    }

private:
    vector<Command*> commands_;
};

class LightOnCommand : public Command {
public:
    LightOnCommand(Light* light) {
        light_ = light;
    }
    void execute() override {
        light_->on();
    }
    void undo() override {
        light_->off();
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
    void undo() override {
        light_->on();
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
    void undo() override {
        stereo_->off();
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
    void undo() override {
        stereo_->on();
    }
    string getName() override {
        return "StereoOffCommand";
    }

private:
    Stereo* stereo_;
};

class RemoteControlWithUndo {
public:
    RemoteControlWithUndo() {
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
        undoCommand = onCommands_.at(slot);
    }
    void offButtonWasPressed(int slot) {
        offCommands_.at(slot)->execute();
        undoCommand = offCommands_.at(slot);
    }
    void undoButtonWasPushed() {
        undoCommand->undo();
    }
    void printCommands() {
        cout << "\n------ Remote Control ------\n";
        for (int i = 0; i < onCommands_.size(); ++i) {
            cout << "[slot " << i << "] " << onCommands_[i]->getName() << '\t' << offCommands_[i]->getName() << "\n";
        }
        cout << "Last command was " << undoCommand->getName() << '\n';
    }

private:
    vector<Command*> onCommands_;
    vector<Command*> offCommands_;
    NoCommand no_command_;
    Command* undoCommand = &no_command_;
};

int main() {
    RemoteControlWithUndo remote;

    Light livingRoomLight("Living Room");
    LightOnCommand livingRoomLightOn(&livingRoomLight);
    LightOffCommand livingRoomLightOff(&livingRoomLight);

    Stereo stereo("Living Room");
    StereoOnWithCDCommand stereoOnWithCdCommand(&stereo);
    StereoOffCommand stereoOffCommand(&stereo);

    vector<Command*> partyOn = { &livingRoomLightOn, &stereoOnWithCdCommand };
    vector<Command*> partyOff = { &livingRoomLightOff, &stereoOffCommand };

    MacroCommand partyOnMacro(partyOn);
    MacroCommand partyOffMacro(partyOff);

    remote.setCommand(0, &partyOnMacro, &partyOffMacro);

    remote.onButtonWasPressed(0);
    remote.undoButtonWasPushed();

    return 0;
}
