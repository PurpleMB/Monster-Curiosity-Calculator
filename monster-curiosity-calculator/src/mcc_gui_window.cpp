#include "mcc_gui_windows.h"

#include <cstdlib>

#include <d3d9.h>
#include <tchar.h>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "app.h"
#include "database.h"

namespace monster_calculator {
void DrawWelcomeWindow(const int windowSettings, const char* databasePath, const char* jsonPath) {
	ImGui::Begin("Database Generation", nullptr, windowSettings);
	if (ImGui::Button("Build Monster Database")) {
		createDatabase(databasePath);
		deleteTable(databasePath);
		createTable(databasePath);
	}
	if (ImGui::Button("Parse Monster Json Info Into Database")) {
		clearTable(databasePath);
		insertDataFromJson(databasePath, jsonPath);
	}
	ImGui::End();
}

void DrawSetParameterWindow(const int windowSettings) {
	static int selected_type = -1;
	const char* types[] = { "Any", "None", "Normal", "Grass" , "Water", "Fire" };

	std::string selected_type_name = (selected_type == -1) ? "Any" : types[selected_type];

	ImGui::Begin("Type Selection", nullptr, windowSettings);

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

	if (ImGui::Button("Find Matching Monsters")) {

	}
	ImGui::End();
}

void DrawValueParameterWindow() {

}

void DrawSetDisplayWindow() {

}

void DrawOutputLogWindow(const int windowSettings) {
	ImGui::Begin("Answer Calculation", nullptr, windowSettings);

	ImGui::Text("# of Results: ");
	ImGui::SameLine();
	ImGui::Text("XXX");

	ImGui::Text("Results:");
	ImVec2 outer_size = ImVec2(0.0f, 400.0f);
	if (ImGui::BeginTable("table_results", 3, ImGuiTableFlags_ScrollY, outer_size))
	{
		ImGui::EndTable();
	}

	ImGui::End();
}
} // namespace monster_calculator