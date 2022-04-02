#ifndef PATTERNS_MODEL_H
#define PATTERNS_MODEL_H

#include <unordered_set>
#include "wx/wx.h"

using namespace std;

class BeatObserver;
class BPMObserver;

class BeatModelInterface {
public:
    virtual void initialize() = 0;

    virtual void on() = 0;
    virtual void off() = 0;

    virtual void setBPM(int) = 0;
    virtual int getBPM() const = 0;

    virtual void registerObserver(BeatObserver*) = 0;
    virtual void removeObserver(BeatObserver*) = 0;

    virtual void registerObserver(BPMObserver*) = 0;
    virtual void removeObserver(BPMObserver*) = 0;
};

class BeatObserver {
public:
    virtual void updateBeat() = 0;
};

class BPMObserver {
public:
    virtual void updateBPM() = 0;
};

class BeatModel : public BeatModelInterface {
private:
    unordered_set<BeatObserver*> beat_observers_;
    unordered_set<BPMObserver*> bpm_observers_;

    int bpm_{ 30 };
    wxTimer timer_;

public:
    void initialize() override;
    void OnTimer(wxTimerEvent &event);

    void on() override;
    void off() override;

    void setBPM(int bpm) override;
    int getBPM() const override;

    void playBeat();
    void stopBeat();

    void registerObserver(BeatObserver* observer) override;
    void removeObserver(BeatObserver* observer) override;

    void registerObserver(BPMObserver* observer) override;
    void removeObserver(BPMObserver* observer) override;

    void notifyBeatObservers();
    void notifyBPMObservers();
};

#endif // PATTERNS_VIEW_H