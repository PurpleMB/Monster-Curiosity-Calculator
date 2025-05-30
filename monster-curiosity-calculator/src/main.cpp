#include <string>
#include "app.h"
#include "database.h"

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

            ImGui::Begin("Database Generation", nullptr, DEFAULT_WINDOW_SETTINGS);
            if (ImGui::Button("Build Monster Database")) {
                createDatabase(DB_PATH.c_str());
                deleteTable(DB_PATH.c_str());
                createTable(DB_PATH.c_str());
            }
            if (ImGui::Button("Parse Monster Json Info Into Database")) {
                clearTable(DB_PATH.c_str());
                insertDataFromJson(DB_PATH.c_str(), JSON_PATH.c_str());
            }

            window_pos[1] += MARGIN + ImGui::GetWindowHeight();

            ImGui::End();
        }

        // type selection window
        {
            static int selected_type = -1;
            const char* types[] = {"Any", "None", "Normal", "Grass" , "Water", "Fire"};
            
            std::string selected_type_name = (selected_type == -1) ? "Any" : types[selected_type];

            ImGui::SetNextWindowSize({ window_size[0], window_size[1] });
            ImGui::SetNextWindowPos({ window_pos[0], window_pos[1] });

            ImGui::Begin("Type Selection", nullptr, DEFAULT_WINDOW_SETTINGS);

            ImGui::Text("Select type to search for:");

            ImGui::Text("Primary Type: ");
            ImGui::SameLine();
            if (ImGui::Button(selected_type_name.c_str()))
            {
                ImGui::OpenPopup("Select type");
            }

            if (ImGui::BeginPopup("Select type"))
            {
                for (int i = 0; i < IM_ARRAYSIZE(types); i++)
                {
                    if (ImGui::Selectable(types[i]))
                    {
                        selected_type = i;
                    }
                }
                ImGui::EndPopup();
            }

            ImGui::End();
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