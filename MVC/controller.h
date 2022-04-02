#ifndef PATTERNS_CONTROLLER_H
#define PATTERNS_CONTROLLER_H

#include "model.h"

class ControllerInterface {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void increaseBPM() = 0;
    virtual void decreaseBPM() = 0;
    virtual void setBPM(int bpm) = 0;
};

class DJView;

class BeatController : public ControllerInterface {
private:
    BeatModelInterface* model_;
    DJView* view_;

public:
    BeatController(BeatModelInterface* model);
    void start() override;
    void stop() override;
    void increaseBPM() override;
    void decreaseBPM() override;
    void setBPM(int bpm) override;

    ~BeatController();
};

#endif // PATTERNS_CONTROLLER_H