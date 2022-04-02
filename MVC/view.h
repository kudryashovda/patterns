#ifndef PATTERNS_VIEW_H
#define PATTERNS_VIEW_H

#include "wx/wx.h"
#include "model.h"

class ControllerInterface;
class BeatModelInterface;
class BeatBar;

class DJView : public BPMObserver, public BeatObserver {
private:
    ControllerInterface* controller_;
    BeatModelInterface* model_;
    wxFrame* view_frame_;
    wxPanel* view_panel_;
    BeatBar* beat_bar_;
    wxStaticText* bpm_output_label_;

    wxStaticText* bpm_label_;
    wxTextCtrl* bpm_text_field_;
    wxButton* set_bpm_button_;
    wxButton* increase_bpm_button_;
    wxButton* decrease_bpm_button_;

    wxMenuBar* menu_bar_;
    wxMenu* menu_;
    wxMenuItem* start_menu_item_;
    wxMenuItem* stop_menu_item_;
    wxMenuItem* quit_menu_item_;

    int MENU_ITEMS_START = 9998;
    int MENU_ITEMS_STOP = 9999;
public:
    DJView(ControllerInterface* controller, BeatModelInterface* model);

    void createView();

    void updateBPM() override;
    void updateBeat() override;
    void createControls();

    void enableStopMenuItem();
    void disableStopMenuItem();

    void enableStartMenuItem();
    void disableStartMenuItem();

    void actionPerformed(wxEvent& event);
};

class ControlFrame : public wxFrame {
public:
    explicit ControlFrame(const wxString& title);
};

class BeatBar : public wxFrame {
    wxGauge* gauge_;
    wxStatusBar* status_bar_;
    bool is_gauge_on_ = false;
public:
    explicit BeatBar(const wxString& title);
    void SetStatusBarText(const wxString& title);
    void SetValue(int value);
};

#endif // PATTERNS_VIEW_H