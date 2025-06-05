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

void DrawWelcomeWindow(const int window_settings, const char* database_path, const char* json_path) {
	ImGui::Begin("Database Generation", nullptr, window_settings);
	if (ImGui::Button("Build Monster Database")) {
		CreateDatabase(database_path);
		DeleteTable(database_path);
		CreateTable(database_path);
	}
	if (ImGui::Button("Parse Monster Json Info Into Database")) {
		ClearTable(database_path);
		InsertDataFromJson(database_path, json_path);
	}
	ImGui::End();
}

void DrawSetParameterWindow(const int window_settings) {
	static int selected_type = -1;
	const char* types[] = { "Any", "None", "Normal", "Grass" , "Water", "Fire" };

	std::string selected_type_name = (selected_type == -1) ? "Any" : types[selected_type];

	ImGui::Begin("Type Selection", nullptr, window_settings);

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

void DrawOutputLogWindow(const int window_settings) {
	ImGui::Begin("Answer Calculation", nullptr, window_settings);

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