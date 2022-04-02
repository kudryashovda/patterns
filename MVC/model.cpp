#include "model.h"

using namespace std;

void BeatModel::initialize() {
    timer_.Bind(wxEVT_TIMER, &BeatModel::OnTimer, this);
}

void BeatModel::on() {
    notifyBPMObservers();
    playBeat();
}

void BeatModel::off() {
    stopBeat();
}

void BeatModel::OnTimer(wxTimerEvent& event) {
    timer_.Stop();
    cout << "Beat..." << endl;

    notifyBeatObservers();
    notifyBPMObservers();
    timer_.Start(60000 / bpm_);
}

void BeatModel::setBPM(int bpm) {
    bpm_ = bpm;
    notifyBPMObservers();
}

int BeatModel::getBPM() const {
    return bpm_;
}

void BeatModel::playBeat() {
    timer_.Stop();
    timer_.Start(60000 / bpm_);
}

void BeatModel::stopBeat() {
    timer_.Stop();
}

void BeatModel::registerObserver(BeatObserver* observer) {
    beat_observers_.insert(observer);
}
void BeatModel::removeObserver(BeatObserver* observer) {
    beat_observers_.erase(observer);
}

void BeatModel::registerObserver(BPMObserver* observer) {
    bpm_observers_.insert(observer);
}

void BeatModel::removeObserver(BPMObserver* observer) {
    bpm_observers_.erase(observer);
}

void BeatModel::notifyBeatObservers() {
    for (auto* observer : beat_observers_) {
        observer->updateBeat();
    }
}
void BeatModel::notifyBPMObservers() {
    for (auto* observer : bpm_observers_) {
        observer->updateBPM();
    }
}
