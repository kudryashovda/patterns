#include "controller.h"

#include "view.h"

BeatController::BeatController(BeatModelInterface* model) {
    model_ = model;
    view_ = new DJView(this, model);
    view_->createView();
    view_->createControls();
    view_->disableStopMenuItem();
    view_->enableStartMenuItem();
    model->initialize();
};

void BeatController::start() {
    model_->on();
    view_->disableStartMenuItem();
    view_->enableStopMenuItem();
}
void BeatController::stop() {
    model_->off();
    view_->disableStopMenuItem();
    view_->enableStartMenuItem();
}
void BeatController::increaseBPM() {
    int bpm = model_->getBPM();
    model_->setBPM(bpm + 1);
    
}
void BeatController::decreaseBPM() {
    int bpm = model_->getBPM();
    if (bpm > 0) {
        model_->setBPM(bpm - 1);
    }
}
void BeatController::setBPM(int bpm) {
    model_->setBPM(bpm);
}

BeatController::~BeatController() {
    //    delete view_;
}
