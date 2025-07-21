#pragma once
#include "mcc_gui_windows.h"

#include <cstdlib>

#include <d3d9.h>
#include <tchar.h>

#include <format>
#include <iostream>

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

	static BetterQueryParameter building_parameter(
		parameter_types[0].query_format,
		parameter_types[0].values[0].second
	);

	if (ImGui::Button(selected_parameter_name.c_str())) {
		ImGui::OpenPopup("Select parameter");
	}

	if (ImGui::BeginPopup("Select parameter")) {
		for (int i = 0; i < parameter_types.size(); i++) {
			if (ImGui::Selectable(parameter_types[i].display_name.c_str())) {
				selected_parameter_index = i;
				building_parameter.query_format = parameter_types[selected_parameter_index].query_format;
			}
		}
		ImGui::EndPopup();
	}

	if (parameter_types[selected_parameter_index].GetParameterCategory() == Enumerated) {
		DrawEnumeratorParameterSelector(parameter_types[selected_parameter_index], building_parameter);
	} 
	else if (parameter_types[selected_parameter_index].GetParameterCategory() == Numerical) {
		DrawNumericalParameterSelector(parameter_types[selected_parameter_index], building_parameter);
	}
	else {
		ImGui::SameLine();
		ImGui::Text("ERROR: UNDEFINED PARAMETER TYPE");
	}


	const ImU8 u8_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	static ImU8 parameter_group = 0;

	if (parameter_group > output_environment.subset_parameters.subset_parameters.size()) {
		parameter_group = output_environment.subset_parameters.subset_parameters.size();
	}

	ImGui::Text("Set Parameter Group: ");
	ImGui::SameLine();
	ImGui::InputScalar("##parameter_group", ImGuiDataType_U8, &parameter_group, inputs_step ? &u8_one : NULL, NULL, "%u", flags);


	if (ImGui::Button("Apply Parameter")) {
		output_environment.subset_parameters.AddParameter(building_parameter, parameter_group);
	}


	DrawSubsetParameterTable(output_environment);


	if (ImGui::Button("Clear All Parameters")) {
		output_environment.subset_parameters.ClearAllParameters();
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

void DrawEnumeratorParameterSelector(ParameterType& param_type, BetterQueryParameter& building_parameter) {
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

	building_parameter.query_value = param_type.values[selected_value_index].second;
}

void DrawNumericalParameterSelector(ParameterType& param_type, BetterQueryParameter& building_parameter) {
	static ImU8 lower_bound = 0;
	static ImU8 upper_bound = 255;
	
	std::vector<std::string> parameter_subtypes = {
		"Range",
		"<",
		"<=",
		">",
		">="
	};
	static int selected_subtype_index = 0;

	if (ImGui::Button(parameter_subtypes[selected_subtype_index].c_str())) {
		ImGui::OpenPopup("##Select parameter subtype");
	}

	if (ImGui::BeginPopup("##Select parameter subtype")) {
		for (int i = 0; i < parameter_subtypes.size(); i++) {
			if (ImGui::Selectable(parameter_subtypes[i].c_str())) {
				selected_subtype_index = i;
				upper_bound = 255;
				lower_bound = 0;
			}
		}
		ImGui::EndPopup();
	}

	const ImU8 u8_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;

	if (parameter_subtypes[selected_subtype_index] == "Range") {
		ImGui::Text("Set Lower Bound: ");
		ImGui::SameLine();
		ImGui::InputScalar("##lower_bound", ImGuiDataType_U8, &lower_bound, inputs_step ? &u8_one : NULL, NULL, "%u", flags);

		ImGui::Text("Set Upper Bound: ");
		ImGui::SameLine();
		ImGui::InputScalar("##upper_bound", ImGuiDataType_U8, &upper_bound, inputs_step ? &u8_one : NULL, NULL, "%u", flags);

		building_parameter.query_value = std::format("BETWEEN {0} AND {1}", lower_bound, upper_bound);
	} else {
		ImGui::Text("Set Inequality Value: ");
		ImGui::SameLine();
		ImGui::InputScalar("##inequality_bound", ImGuiDataType_U8, &lower_bound, inputs_step ? &u8_one : NULL, NULL, "%u", flags);
		building_parameter.query_value = std::format("{0} {1}", parameter_subtypes[selected_subtype_index], lower_bound);
	}
}

void DrawSubsetParameterTable(OutputEnvironment& output_environment) {
	ImGui::Text("Current subset parameters:");

	ImVec2 outer_size = ImVec2(0.0f, 400.0f);
	const int kColumnCount = 5;
	const int kTableFlags = ImGuiTableFlags_Borders |
		ImGuiTableFlags_SizingFixedFit |
		ImGuiTableFlags_ScrollY;
	static int frozen_columns = 0;
	static int frozen_rows = 1;
	if (ImGui::BeginTable("table_results", kColumnCount, kTableFlags, outer_size)) {
		// prepare table header
		ImGui::TableSetupColumn("Parameter #", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Parameter Group", ImGuiTableColumnFlags_WidthFixed);
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
		int parameter_count = 0;
		for (int group_index = 0; group_index < output_environment.subset_parameters.subset_parameters.size(); group_index++) {
			std::vector<BetterQueryParameter>& parameter_group = output_environment.subset_parameters.subset_parameters[group_index];
			for (int parameter_index = 0; parameter_index < parameter_group.size(); parameter_index++) {
				BetterQueryParameter& subset_parameter = parameter_group[parameter_index];
				ImGui::TableNextRow();

				ImGui::TableSetColumnIndex(0);
				ImGui::Text(std::to_string(++parameter_count).c_str());

				ImGui::TableSetColumnIndex(1);
				int displayed_group_index = group_index + 1;
				ImGui::Text(std::to_string(displayed_group_index).c_str());

				ImGui::TableSetColumnIndex(2);
				ImGui::Text(subset_parameter.query_format.c_str());

				ImGui::TableSetColumnIndex(3);
				ImGui::Text(subset_parameter.query_value.c_str());

				ImGui::TableSetColumnIndex(4);
				std::string label = std::to_string(parameter_count) + " Remove Parameter";
				if (ImGui::Button(label.c_str())) {
					output_environment.subset_parameters.RemoveParameter(group_index, parameter_index);
				}
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

	static SubsetColumnInfo name_col_info("Name", "pretty_name", true, false);
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

	// pagination of table for performance reasons
	const ImU8 u8_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	static ImU8 subset_page = 0;

	std::vector<std::string> page_size_labels = {"None", "15", "30", "50", "100"};
	std::vector<int> page_sizes = {10000, 15, 30, 50, 100};
	static int selected_page_size_index = 0;
	static int page_size = page_sizes[0];

	ImGui::Text("Page size limit: ");
	ImGui::SameLine();
	if (ImGui::Button(page_size_labels[selected_page_size_index].c_str())) {
		ImGui::OpenPopup("##Select page size limit:");
	}
	if (ImGui::BeginPopup("##Select page size limit:")) {
		for (int i = 0; i < page_size_labels.size(); i++) {
			if (ImGui::Selectable(page_size_labels[i].c_str())) {
				selected_page_size_index = i;
				page_size = page_sizes[i];
			}
		}
		ImGui::EndPopup();
	}

	ImU8 page_count = output_environment.subset_entries.size() / page_size;
	if (subset_page > page_count) {
		subset_page = page_count;
	}
	ImGui::InputScalar("##subset_table_page", ImGuiDataType_U8, &subset_page, inputs_step ? &u8_one : NULL, NULL, "%u", flags);

	// subset display table
	ImVec2 outer_size = ImVec2(0.0f, 400.0f);
	const int kTableFlags = 
		ImGuiTableFlags_Sortable |
		ImGuiTableFlags_Borders |
		ImGuiTableFlags_SizingFixedFit |
		ImGuiTableFlags_ScrollY |
		ImGuiTableFlags_ScrollX;
	static int frozen_columns = 1;
	static int frozen_rows = 1;
	if (ImGui::BeginTable("subset_entries", active_column_count, kTableFlags, outer_size)) {
		// column setup
		int col_id = 0;
		for (SubsetColumnInfo active_column : active_columns) {
			std::string col_name = active_column.display_name;
			ImGui::TableSetupColumn(col_name.c_str(), ImGuiTableColumnFlags_WidthFixed, 0.0f, col_id);
			col_id++;
		}
		ImGui::TableSetupScrollFreeze(frozen_columns, frozen_rows);

		// creating label row
		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
		for (int column = 0; column < active_column_count; column++) {
			ImGui::TableSetColumnIndex(column);
			const char* column_name = ImGui::TableGetColumnName(column);
			ImGui::TableHeader(column_name);
		}

		// table sorting via ImGui
		if (ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()) {
			if (sort_specs->SpecsDirty) {
				std::sort(
					output_environment.subset_entries.begin(),
					output_environment.subset_entries.end(),
					SubsetComparator(sort_specs)
				);
				sort_specs->SpecsDirty = false;
			}
		}

		// printing entry rows
		int starting_index = page_size * subset_page;
		int ending_index = min(output_environment.subset_entries.size(), starting_index + page_size);
		for (int subset_index = starting_index; subset_index < ending_index; subset_index++) {
			auto subset_entry = output_environment.subset_entries[subset_index];
			ImGui::TableNextRow();
			for (SubsetColumnInfo active_column : active_columns) {
				ImGui::TableNextColumn();
				ImGui::Text(subset_entry.GetData(active_column.query_name).c_str());
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