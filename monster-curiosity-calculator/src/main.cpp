#include <string>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "app.h"
#include "database.h"
#include "mcc_gui_windows.h"

// Extends App-provided boilerplate to handle drawing of 
// windows and GUI elements for MCC.
class MCCApp : public App
{
public:
    MCCApp() = default;
    ~MCCApp() = default;

    virtual void StartUp() final
    {
    }

    // Put any logic for the GUI that needs to be drawn every frame in here
    virtual void Update() final
    {
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        std::vector<float> window_size = { 350, 0 };
        std::vector<float> window_pos = { kWindowMargin, kWindowMargin };

        // database generation window
        {
            ImGui::SetNextWindowSize({ window_size[0], window_size[1]});
            ImGui::SetNextWindowPos({window_pos[0], window_pos[1]});

            monster_calculator::DrawWelcomeWindow(kDefaultWindowSettings, kDbPath.c_str(), kJsonPath.c_str());

            window_pos[1] += kWindowMargin + ImGui::GetWindowHeight();
        }

        // type selection window
        {
            ImGui::SetNextWindowSize({ window_size[0], window_size[1] });
            ImGui::SetNextWindowPos({ window_pos[0], window_pos[1] });

            monster_calculator::DrawSetParameterWindow(kDefaultWindowSettings);

            window_pos[1] = kWindowMargin;
            window_pos[0] += kWindowMargin + ImGui::GetWindowWidth();
        }

        // answer calculation window
        {
            ImGui::SetNextWindowSize({ window_size[0], window_size[1] });
            ImGui::SetNextWindowPos({ window_pos[0], window_pos[1] });

            monster_calculator::DrawOutputLogWindow(kDefaultWindowSettings);
        }
    }

private:
    bool show_demo_window = true;
    bool show_another_window = false;

    const std::string kDbPath = "c:\\DB_TEST\\test.db";
    const std::string kJsonPath = "c:\\DB_TEST\\mccdata.json";

    const int kDefaultWindowSettings = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    const float kWindowMargin = 25;
};

// Main code
int main(int, char**)
{
    MCCApp app;
    app.Run();

    return 0;
}