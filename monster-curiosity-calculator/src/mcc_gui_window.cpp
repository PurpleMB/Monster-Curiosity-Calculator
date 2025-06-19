#include "mcc_gui_windows.h"

#include <cstdlib>

#include <d3d9.h>
#include <tchar.h>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "app.h"
#include "database.h"
#include "mcc_structs.h"

namespace monster_calculator {

void DrawWelcomeWindow(WindowParameters& window_parameters) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	if (ImGui::Button("Build Monster Database")) {
		CreateDatabase();
		DeleteMainTable();
		CreateMainTable();
	}
	if (ImGui::Button("Parse Monster Json Info Into Database")) {
		ClearMainTable();
		InsertDataFromJson();
	}

	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}

void DrawSetParameterWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	ImGui::Text("Select type to search for:");

	static int selected_type = -1;
	const char* types[] = {"Any", "None", "Normal", "Fire", "Fighting", "Water", "Flying", "Grass", 
						   "Poison", "Electric", "Ground", "Psychic", "Rock", 
						   "Ice", "Bug", "Dragon", "Ghost", "Dark", "Steel", "Fairy"};
	std::string selected_type_name = (selected_type == -1) ? "Any" : types[selected_type];

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
		QueryParameter query_param;
		query_param.parameter_name = "primary_type";
		query_param.parameter_value = selected_type_name;
		for (char& c : query_param.parameter_value) {
			c = std::tolower(static_cast<unsigned char>(c));
		}
		QueryDatabase(query_param, output_environment);
	}

	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}

void DrawValueParameterWindow(WindowParameters& window_parameters) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	if (ImGui::Button("Query Database")) {
		
	}

	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}

void DrawSetDisplayWindow(WindowParameters& window_parameters) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}

void DrawOutputLogWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	ImGui::Text(output_environment.result_count_text.c_str());

	ImGui::Text("Log:");
	ImVec2 outer_size = ImVec2(400.0f, 400.0f);
	if (ImGui::BeginTable("table_results", 1, ImGuiTableFlags_ScrollY, outer_size))
	{
		for (std::string query_output : output_environment.query_result_texts) {
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(query_output.c_str());
		}
		/*
		for (int row = 0; row < 4; row++) {
			ImGui::TableNextRow();
			for (int column = 0; column < 3; column++) {
				ImGui::TableSetColumnIndex(column);
				ImGui::Text("Row %d Column %d", row, column);
			}
		}
		*/
		ImGui::EndTable();
	}

	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}

} // namespace monster_calculator