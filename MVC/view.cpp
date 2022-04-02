#include "view.h"

#include "controller.h"
#include "model.h"

DJView::DJView(ControllerInterface* controller, BeatModelInterface* model) {
    controller_ = controller;
    model_ = model;
    model->registerObserver(dynamic_cast<BeatObserver*>(this));
    model->registerObserver(dynamic_cast<BPMObserver*>(this));
}

void DJView::createView() {
    view_frame_ = new ControlFrame("Control");
    beat_bar_ = new BeatBar("View");
}

void DJView::updateBPM() {
    int bpm = model_->getBPM();
    if (bpm == 0) {
        beat_bar_->SetStatusBarText("Offline");
    } else {
        beat_bar_->SetStatusBarText("Current BPM: " + to_string(bpm));
    }
    beat_bar_->SetValue(bpm);
}

void DJView::updateBeat() {
    bpm_text_field_->SetValue(to_string(model_->getBPM()));
}

void DJView::createControls() {
    menu_bar_ = new wxMenuBar;
    menu_ = new wxMenu;

    start_menu_item_ = menu_->Append(MENU_ITEMS_START, wxT("Start"));
    stop_menu_item_ = menu_->Append(MENU_ITEMS_STOP, wxT("Stop"));
    quit_menu_item_ = menu_->Append(wxID_EXIT, wxT("Quit"));
    
    menu_->Bind(wxEVT_COMMAND_MENU_SELECTED, &DJView::actionPerformed, this);

    menu_bar_->Append(menu_, wxT("DJ Control"));
    view_frame_->SetMenuBar(menu_bar_);

    view_panel_ = new wxPanel(view_frame_);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);

    bpm_label_ = new wxStaticText(view_panel_, wxID_ANY, "Enter BPM:");
    bpm_text_field_ = new wxTextCtrl(view_panel_, wxID_ANY, "30");

    hbox1->Add(bpm_label_, 0, wxEXPAND | wxALL, 0);
    hbox1->Add(bpm_text_field_, 1, wxEXPAND | wxALL, 0);

    vbox->Add(hbox1, 0, wxEXPAND | wxALL, 0);

    set_bpm_button_ = new wxButton(view_panel_, wxID_ANY, "Set");
    set_bpm_button_->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &DJView::actionPerformed, this);

    vbox->Add(set_bpm_button_, 0, wxEXPAND | wxALL, 0);

    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);

    decrease_bpm_button_ = new wxButton(view_panel_, wxID_ANY, "<<");
    increase_bpm_button_ = new wxButton(view_panel_, wxID_ANY, ">>");

    decrease_bpm_button_->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &DJView::actionPerformed, this);
    increase_bpm_button_->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &DJView::actionPerformed, this);

    hbox2->Add(decrease_bpm_button_, 1, wxEXPAND | wxALL, 0);
    hbox2->Add(increase_bpm_button_, 1, wxEXPAND | wxALL, 0);

    vbox->Add(hbox2, 0, wxEXPAND | wxALL, 0);

    view_panel_->SetSizer(vbox);

    vbox->Fit(view_frame_);
    view_frame_->SetMinSize(view_frame_->GetSize());

    view_frame_->Centre();
    view_frame_->Show(true);
}

void DJView::enableStopMenuItem() {
    stop_menu_item_->Enable(true);
}

void DJView::disableStopMenuItem() {
    stop_menu_item_->Enable(false);
}

void DJView::enableStartMenuItem() {
    start_menu_item_->Enable(true);
}
void DJView::disableStartMenuItem() {
    start_menu_item_->Enable(false);
}

void DJView::actionPerformed(wxEvent& event) {
    if (event.GetEventObject() == set_bpm_button_) {
        int bpm = wxAtoi(bpm_text_field_->GetValue());
        controller_->setBPM(bpm);
    } else if (event.GetEventObject() == increase_bpm_button_) {
        controller_->increaseBPM();
    } else if (event.GetEventObject() == decrease_bpm_button_) {
        controller_->decreaseBPM();
    } else if (event.GetId() == MENU_ITEMS_START) {
        controller_->start();
    } else if (event.GetId() == MENU_ITEMS_STOP) {
        controller_->stop();
    }
}

ControlFrame::ControlFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title) {
}

BeatBar::BeatBar(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title) {

    auto* panel = new wxPanel(this);
    auto* vbox = new wxBoxSizer(wxVERTICAL);

    gauge_ = new wxGauge(panel, wxID_ANY, 100);
    gauge_->SetValue(0);
    vbox->Add(gauge_, 1, wxEXPAND | wxALL, 0);
    panel->SetSizer(vbox);

    status_bar_ = new wxStatusBar(this);
    status_bar_->SetFieldsCount(1);
    status_bar_->SetStatusText("Current BPM:", 0);
    wxFrame::SetStatusBar(status_bar_);

    this->SetSize(wxSize(200, 80));
    this->SetMinSize(this->GetSize());

    Show(true);
}

void BeatBar::SetStatusBarText(const wxString& text) {
    status_bar_->SetStatusText(text);
}

void BeatBar::SetValue(int value) {
    gauge_->SetValue(value);
}
