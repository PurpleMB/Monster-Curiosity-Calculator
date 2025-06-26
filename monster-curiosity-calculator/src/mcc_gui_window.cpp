#pragma once
#include "mcc_gui_windows.h"

#include <cstdlib>

#include <d3d9.h>
#include <tchar.h>

#include <format>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "app.h"
#include "database.h"
#include "mcc_structs.h"
#include "mcc_constants.h"

namespace monster_calculator {

void DrawWelcomeWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	if (ImGui::Button("Build Monster Database")) {
		CreateDatabase(output_environment);
		DeleteMainTable(output_environment);
		CreateMainTable(output_environment);
	}
	if (ImGui::Button("Parse Monster Json Info Into Database")) {
		ClearMainTable(output_environment);
		InsertDataFromJson(output_environment);
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

	ImGui::Text("Select parameter to filter by:");

	std::vector<ParameterType> parameter_types = {kPrimaryTypeParam, kSecondaryTypeParam, kEitherTypeParam, kHealthParam};
	static int selected_parameter_index = 0;
	std::string selected_parameter_name = parameter_types[selected_parameter_index].display_name;

	if (ImGui::Button(selected_parameter_name.c_str())) {
		ImGui::OpenPopup("Select parameter");
	}

	if (ImGui::BeginPopup("Select parameter")) {
		for (int i = 0; i < parameter_types.size(); i++) {
			if (ImGui::Selectable(parameter_types[i].display_name.c_str())) {
				selected_parameter_index = i;
			}
		}
		ImGui::EndPopup();
	}

	if (parameter_types[selected_parameter_index].GetParameterCategory() == Enumerated) {
		ImGui::SameLine();
		DrawEnumeratorParameterSelector(parameter_types[selected_parameter_index], output_environment);
	} 
	else if (parameter_types[selected_parameter_index].GetParameterCategory() == Numerical) {
		ImGui::SameLine();
		ImGui::Text("NUMERICAL PARAMETER");
	}
	else {
		ImGui::SameLine();
		ImGui::Text("UNDEFINED PARAMETER TYPE");
	}

	if (ImGui::Button("Find Matching Monsters")) {
		CreateSubtable(output_environment);
		SortSubtableEntries(output_environment);
	}

	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}

void DrawEnumeratorParameterSelector(ParameterType& param_type, OutputEnvironment& output_environment) {
	static int selected_value_index = 0;

	std::string selected_value_name = param_type.values[selected_value_index].first;
	if (ImGui::Button(selected_value_name.c_str())) {
		ImGui::OpenPopup("Select parameter value");
	}

	if (ImGui::BeginPopup("Select parameter value")) {
		for (int i = 0; i < param_type.values.size(); i++) {
			if (ImGui::Selectable(param_type.values[i].first.c_str())) {
				selected_value_index = i;
			}
		}
		ImGui::EndPopup();
	}

	ImGui::SameLine();
	if (ImGui::Button("Apply Parameter")) {
		BetterQueryParameter subset_parameter(
			param_type.query_format,
			param_type.values[selected_value_index].second
		);
		output_environment.subset_parameters.push_back(subset_parameter);
	}
}

void DrawValueParameterWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	ImGui::Text("Choose value to calculate:");
	if (ImGui::Button("TODO: Calculate value")) {
		
	}

	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	ImGui::End();
}

void DrawSetDisplayWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}

	// text line showing # of entries in subset
	std::string subset_size_text = "Subset Size: " + std::to_string(output_environment.subset_entries.size());
	ImGui::Text(subset_size_text.c_str());

	// subset table sorting fields
	ImGui::Text("Sort entries by:");

	std::vector<std::string> sortable_parameters = {"ID #", "Name", "Stat Total"};
	std::vector<std::string> sortable_query_params = {"dex_number", "name", "stat_total"};
	static int selected_parameter_index = 0;
	std::string selected_sorting_param_name = sortable_parameters[selected_parameter_index];

	std::vector<std::string> sortable_directions = {"Ascending", "Descending"};
	std::vector<std::string> sortable_query_directions = {"asc", "desc"};
	static int selected_direction_index = 0;
	std::string selected_sorting_name = sortable_directions[selected_direction_index];
	
	if (ImGui::Button(selected_sorting_param_name.c_str())) {
		ImGui::OpenPopup("Select sorting parameter");
	}
	ImGui::SameLine();
	if (ImGui::Button(selected_sorting_name.c_str())) {
		ImGui::OpenPopup("Select sorting direction");
	}
	ImGui::SameLine();
	if (ImGui::Button("Apply")) {
		/*
		std::string selected_query_param = sortable_query_params[selected_parameter_index];
		std::string selected_query_dir = sortable_query_directions[selected_direction_index];
		QueryParameter sorting_param(selected_query_param, selected_query_dir);
		output_environment.sorting_parameter = sorting_param;
		SortSubtableEntries(output_environment);
		*/
	}

	if (ImGui::BeginPopup("Select sorting parameter")) {
		for (int i = 0; i < sortable_parameters.size(); i++) {
			if (ImGui::Selectable(sortable_parameters[i].c_str())) {
				selected_parameter_index = i;
			}
		}
		ImGui::EndPopup();
	}
	if (ImGui::BeginPopup("Select sorting direction")) {
		for (int i = 0; i < sortable_directions.size(); i++) {
			if (ImGui::Selectable(sortable_directions[i].c_str())) {
				selected_direction_index = i;
			}
		}
		ImGui::EndPopup();
	}


	// subset display table
	ImVec2 outer_size = ImVec2(0.0f, 300.0f);
	const int kColumnCount = 3;
	const int kTableFlags = ImGuiTableFlags_Borders |
		ImGuiTableFlags_SizingStretchSame |
		ImGuiTableFlags_ScrollY;
	if (ImGui::BeginTable("subset_entries", kColumnCount, kTableFlags, outer_size)) {
		int subset_size = output_environment.subset_entries.size();
		int subset_index = 0;
		while(subset_index < subset_size) {
		//for (std::string subset_entry : output_environment.subset_entries) {
			ImGui::TableNextRow();
			for (int column_index = 0; column_index < 3; column_index++) {
				ImGui::TableSetColumnIndex(column_index);
				std::string subset_entry = output_environment.subset_entries[subset_index];
				ImGui::Text(subset_entry.c_str());
				subset_index++;
				if (subset_index >= subset_size) {
					break;
				}
			}
		}
		ImGui::EndTable();
	}

	ImGui::End();
}

void DrawOutputLogWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	ImVec2 outer_size = ImVec2(0.0f, 300.0f);
	const int kColumnCount = 4;
	const int kTableFlags = ImGuiTableFlags_Borders | 
							ImGuiTableFlags_SizingFixedFit |
							ImGuiTableFlags_ScrollY;
	static int frozen_columns = 0;
	static int frozen_rows = 1;
	if (ImGui::BeginTable("table_results", kColumnCount, kTableFlags, outer_size))
	{
		// prepare table header
		ImGui::TableSetupColumn("Entry #",		ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Timestamp",	ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Event Code",	ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Message",		ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupScrollFreeze(frozen_columns, frozen_rows);

		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
		for (int column = 0; column < kColumnCount; column++) {
			ImGui::TableSetColumnIndex(column);
			const char* column_name = ImGui::TableGetColumnName(column);
			ImGui::TableHeader(column_name);
		}
		


		// print log entries
		for (int i = 0; i < output_environment.log_entries.size(); i++) {
			LogEntry entry = output_environment.log_entries[i];

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			int displayed_index = i + 1;
			ImGui::Text(std::to_string(displayed_index).c_str());

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(entry.timestamp.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text(entry.message_code.c_str());

			ImGui::TableSetColumnIndex(3);
			ImGui::TextWrapped(entry.log_message.c_str());
		}
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