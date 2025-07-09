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

	std::vector<ParameterType> parameter_types = {kPrimaryTypeParam, kSecondaryTypeParam, kEitherTypeParam, kHealthParam, kRegionParam};
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
		DrawEnumeratorParameterSelector(parameter_types[selected_parameter_index], output_environment);
	} 
	else if (parameter_types[selected_parameter_index].GetParameterCategory() == Numerical) {
		DrawNumericalParameterSelector(parameter_types[selected_parameter_index], output_environment);
	}
	else {
		ImGui::SameLine();
		ImGui::Text("ERROR: UNDEFINED PARAMETER TYPE");
	}

	DrawSubsetParameterTable(output_environment);

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

void DrawNumericalParameterSelector(ParameterType& param_type, OutputEnvironment& output_environment) {
	const ImU8 u8_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;

	static ImU8 lower_bound = 255;
	ImGui::Text("Set Lower Bound: ");
	ImGui::SameLine();
	ImGui::InputScalar("##lower_bound", ImGuiDataType_U8, &lower_bound, inputs_step ? &u8_one : NULL, NULL, "%u", flags);

	static ImU8 upper_bound = 255;
	ImGui::Text("Set Upper Bound: ");
	ImGui::SameLine();
	ImGui::InputScalar("##upper_bound", ImGuiDataType_U8, &upper_bound, inputs_step ? &u8_one : NULL, NULL, "%u", flags);

	if (ImGui::Button("Apply Parameter")) {
		BetterQueryParameter subset_parameter(
			param_type.query_format,
			std::format("{0} AND {1}", lower_bound, upper_bound)
		);
		output_environment.subset_parameters.push_back(subset_parameter);
	}
}

void DrawSubsetParameterTable(OutputEnvironment& output_environment) {
	ImGui::Text("Current subset parameters:");

	ImVec2 outer_size = ImVec2(0.0f, 400.0f);
	const int kColumnCount = 4;
	const int kTableFlags = ImGuiTableFlags_Borders |
		ImGuiTableFlags_SizingFixedFit |
		ImGuiTableFlags_ScrollY;
	static int frozen_columns = 0;
	static int frozen_rows = 1;
	if (ImGui::BeginTable("table_results", kColumnCount, kTableFlags, outer_size)) {
		// prepare table header
		ImGui::TableSetupColumn("Parameter #", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Column", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupScrollFreeze(frozen_columns, frozen_rows);

		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
		for (int column = 0; column < kColumnCount; column++) {
			ImGui::TableSetColumnIndex(column);
			const char* column_name = ImGui::TableGetColumnName(column);
			ImGui::TableHeader(column_name);
		}



		// print log entries
		for (int i = 0; i < output_environment.subset_parameters.size(); i++) {
			BetterQueryParameter subset_parameter = output_environment.subset_parameters[i];
			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);
			int displayed_index = i + 1;
			ImGui::Text(std::to_string(displayed_index).c_str());

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(subset_parameter.query_format.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text(subset_parameter.query_value.c_str());

			ImGui::TableSetColumnIndex(3);
			std::string label = std::to_string(i) + " Remove Parameter";
			if (ImGui::Button(label.c_str())) {
				output_environment.subset_parameters.erase(output_environment.subset_parameters.begin() + i);
			}
		}
		ImGui::EndTable();
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

	// text line showing # of entries in subset
	std::string subset_size_text = "Subset Size: " + std::to_string(output_environment.subset_entries.size());
	ImGui::Text(subset_size_text.c_str());

	static SubsetColumnInfo name_col_info("Name", "name", true, false);
	static SubsetColumnInfo dex_col_info("Dex #", "dex_number", false, true);
	static SubsetColumnInfo color_info("Color", "color", false, true);
	static SubsetColumnInfo shape_info("Shape", "shape", false, true);
	static SubsetColumnInfo height_info("Height (m)", "height", false, true);
	static SubsetColumnInfo weight_info("Weight (kg)", "weight", false, true);
	static SubsetColumnInfo prim_type_info("Primary Type", "primary_type", false, true);
	static SubsetColumnInfo sec_type_info("Secondary Type", "secondary_type", false, true);

	static std::vector<SubsetColumnInfo> column_infos = {
		name_col_info, 
		dex_col_info,
		color_info,
		shape_info,
		height_info,
		weight_info,
		prim_type_info,
		sec_type_info
	};
	
	if (ImGui::TreeNode("Column Options")) {
		for (SubsetColumnInfo& col_info : column_infos) {
			if (col_info.togglable) {
				ImGui::Checkbox(col_info.display_name.c_str(), &col_info.enabled);
			}
		}
		ImGui::TreePop();
	}

	std::vector<SubsetColumnInfo> active_columns = {};
	for (SubsetColumnInfo& col_info : column_infos) {
		if (col_info.enabled) {
			active_columns.push_back(col_info);
		}
	}
	int active_column_count = active_columns.size();
	ImGui::Text("Active Columns: %d", active_column_count);

	// subset display table
	ImVec2 outer_size = ImVec2(0.0f, 400.0f);
	const int kTableFlags = 
		ImGuiTableFlags_Borders |
		ImGuiTableFlags_SizingFixedFit |
		ImGuiTableFlags_ScrollY |
		ImGuiTableFlags_ScrollX;
	static int frozen_columns = 1;
	static int frozen_rows = 1;
	if (ImGui::BeginTable("subset_entries", active_column_count, kTableFlags, outer_size)) {
		// column setup
		for (SubsetColumnInfo active_column : active_columns) {
			std::string col_name = active_column.display_name;
			ImGui::TableSetupColumn(col_name.c_str(), ImGuiTableColumnFlags_WidthFixed);
		}
		ImGui::TableSetupScrollFreeze(frozen_columns, frozen_rows);

		// creating label row
		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
		for (int column = 0; column < active_column_count; column++) {
			ImGui::TableSetColumnIndex(column);
			const char* column_name = ImGui::TableGetColumnName(column);
			ImGui::TableHeader(column_name);
		}

		// printing entry rows
		for (auto subset_entry : output_environment.subset_entries) {
			ImGui::TableNextRow();
			for (SubsetColumnInfo active_column : active_columns) {
				ImGui::TableNextColumn();
				ImGui::Text(subset_entry[active_column.query_name].c_str());
			}
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