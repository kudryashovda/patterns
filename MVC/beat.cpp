#include "model.h"
#include "controller.h"

#include <memory>
#include <wx/wx.h>

using namespace std;

class MyApp: public wxApp
{
public:
	bool OnInit() override;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    BeatModelInterface* beat_model = new BeatModel;
    ControllerInterface* controller = new BeatController(beat_model);

	return true;
}

