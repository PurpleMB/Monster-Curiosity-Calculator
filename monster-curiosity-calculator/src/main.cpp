#include <string>
#include "app.h"
#include "database.h"
#include "mcc_gui_windows.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

class MCCApp : public App
{
public:
    const std::string DB_PATH = "c:\\DB_TEST\\test.db";
    const std::string JSON_PATH = "c:\\DB_TEST\\mccdata.json";

    const int DEFAULT_WINDOW_SETTINGS = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

    const float MARGIN = 25;

    MCCApp() = default;
    ~MCCApp() = default;

    virtual void StartUp() final
    {

    }

    virtual void Update() final
    {
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        std::vector<float> window_size = { 350, 0 };
        std::vector<float> window_pos = { MARGIN, MARGIN };

        // database generation window
        {
            ImGui::SetNextWindowSize({ window_size[0], window_size[1]});
            ImGui::SetNextWindowPos({window_pos[0], window_pos[1]});

            monster_calculator::DrawWelcomeWindow(DEFAULT_WINDOW_SETTINGS, DB_PATH.c_str(), JSON_PATH.c_str());

            window_pos[1] += MARGIN + ImGui::GetWindowHeight();
        }

        // type selection window
        {
            ImGui::SetNextWindowSize({ window_size[0], window_size[1] });
            ImGui::SetNextWindowPos({ window_pos[0], window_pos[1] });

            monster_calculator::DrawSetParameterWindow(DEFAULT_WINDOW_SETTINGS);

            window_pos[1] = MARGIN;
            window_pos[0] += MARGIN + ImGui::GetWindowWidth();
        }

        // answer calculation window
        {
            ImGui::SetNextWindowSize({ window_size[0], window_size[1] });
            ImGui::SetNextWindowPos({ window_pos[0], window_pos[1] });

            monster_calculator::DrawOutputLogWindow(DEFAULT_WINDOW_SETTINGS);
        }
    }

private:
    bool show_demo_window = true;
    bool show_another_window = false;
};

// Main code
int main(int, char**)
{
    MCCApp app;
    app.Run();

    return 0;
}