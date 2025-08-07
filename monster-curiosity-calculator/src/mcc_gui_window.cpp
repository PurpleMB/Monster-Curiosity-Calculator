#pragma once
#include "mcc_gui_windows.h"

#include <cstdlib>

#include <d3d9.h>
#include <tchar.h>

#include <vector>
#include <format>
#include <iostream>
#include <cstring> // for strcmp
#include <memory>
#include <algorithm> // for clamp, min, and max

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "app.h"
#include "database.h"
#include "mcc_structs.h"
#include "mcc_constants.h"
#include "mcc_parameter_structs.h"
#include "mcc_parameter_constants.h"

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

void DrawSetParameterWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment,
	std::vector<std::shared_ptr<ParameterType>> parameter_types) 
{
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	ImGui::Text("Select parameter to filter by:");

	static int selected_parameter_index = 0;
	std::string selected_parameter_name = parameter_types[selected_parameter_index]->display_name;

	static QueryParameter building_parameter;

	if (ImGui::Button(selected_parameter_name.c_str())) {
		ImGui::OpenPopup("Select parameter");
	}

	if (ImGui::BeginPopup("Select parameter")) {
		for (int i = 0; i < parameter_types.size(); i++) {
			if (ImGui::Selectable(parameter_types[i]->display_name.c_str())) {
				selected_parameter_index = i;
			}
		}
		ImGui::EndPopup();
	}

	ParameterType* selected_param = parameter_types[selected_parameter_index].get();
	building_parameter.database_statement.format = selected_param->database_format;
	building_parameter.display_statement.format = selected_param->display_format;
	building_parameter.display_statement.parameter_color = selected_param->parameter_color;

	if (parameter_types[selected_parameter_index]->GetParameterCategory() == Enumerated) {
		EnumeratedParameterType enum_param = *dynamic_cast<EnumeratedParameterType*>(selected_param);
		DrawEnumeratorParameterSelector(enum_param, building_parameter);
	} 
	else if (parameter_types[selected_parameter_index]->GetParameterCategory() == Numerical) {
		NumericalParameterType numer_param = *dynamic_cast<NumericalParameterType*>(selected_param);
		DrawNumericalParameterSelector(numer_param, building_parameter);
	}
	else {
		ImGui::SameLine();
		ImGui::Text("ERROR: UNDEFINED PARAMETER TYPE");
	}


	const ImU8 u8_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	static ImU8 parameter_group = 0;

	if (parameter_group > output_environment.subset_parameters.GetGroupCount()) {
		parameter_group = output_environment.subset_parameters.GetGroupCount();
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

void DrawEnumeratorParameterSelector(EnumeratedParameterType& param_type, QueryParameter& building_parameter) {
	static int selected_value_index = 0;

	std::string selected_value_name = param_type.values[selected_value_index].display_name;
	if (ImGui::Button(selected_value_name.c_str())) {
		ImGui::OpenPopup("Select parameter value");
	}

	if (ImGui::BeginPopup("Select parameter value")) {
		for (int i = 0; i < param_type.values.size(); i++) {
			if (ImGui::Selectable(param_type.values[i].display_name.c_str())) {
				selected_value_index = i;
			}
		}
		ImGui::EndPopup();
	}

	building_parameter.database_statement.argument = param_type.values[selected_value_index].database_name;
	building_parameter.display_statement.parameter_name = param_type.display_name;
	building_parameter.display_statement.argument = param_type.values[selected_value_index].display_name;
	//building_parameter.display_statement.parameter_color = param_type.
	building_parameter.display_statement.argument_color = param_type.values[selected_value_index].value_color;
}

void DrawNumericalParameterSelector(NumericalParameterType& param_type, QueryParameter& building_parameter) {
	int min_val = param_type.min_value;
	int max_val = param_type.max_value;
	
	static int selected_subtype_index = 0;
	std::vector<ParameterValue> operations = param_type.operations;
	if (ImGui::Button(operations[selected_subtype_index].display_name.c_str())) {
		ImGui::OpenPopup("##Select parameter subtype");
	}

	if (ImGui::BeginPopup("##Select parameter subtype")) {
		for (int i = 0; i < operations.size(); i++) {
			if (ImGui::Selectable(operations[i].display_name.c_str())) {
				selected_subtype_index = i;
			}
		}
		ImGui::EndPopup();
	}

	const int u32_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EscapeClearsAll;

	if (operations[selected_subtype_index].display_name == "Range") {
		static int lower_bound = min_val;
		static int upper_bound = max_val;

		ImGui::Text("Set Lower Bound: ");
		ImGui::SameLine();
		ImGui::InputScalar("##lower_bound", ImGuiDataType_U32, &lower_bound, inputs_step ? &u32_one : NULL, NULL, "%u", flags);

		ImGui::Text("Set Upper Bound: ");
		ImGui::SameLine();
		ImGui::InputScalar("##upper_bound", ImGuiDataType_U32, &upper_bound, inputs_step ? &u32_one : NULL, NULL, "%u", flags);

		int lower_max = std::min<int>(max_val, upper_bound);
		lower_bound = std::clamp(lower_bound, min_val, lower_max);
		int upper_min = std::max<int>(min_val, lower_bound);
		upper_bound = std::clamp(upper_bound, upper_min, max_val);

		building_parameter.database_statement.argument = std::format("BETWEEN {0} AND {1}", lower_bound, upper_bound);
		building_parameter.display_statement.parameter_name = param_type.display_name;
		building_parameter.display_statement.argument = std::format("[{0}, {1}]", lower_bound, upper_bound);
		building_parameter.display_statement.argument_color = operations[selected_subtype_index].value_color;
	} else {
		static int bound = min_val;
		ImGui::Text("Set Inequality Value: ");
		ImGui::SameLine();
		ImGui::InputScalar("##inequality_bound", ImGuiDataType_U32, &bound, inputs_step ? &u32_one : NULL, NULL, "%u", flags);

		bound = std::clamp(bound, min_val, max_val);

		building_parameter.database_statement.argument = std::format("{0} {1}", operations[selected_subtype_index].database_name, bound);
		building_parameter.display_statement.parameter_name = param_type.display_name;
		building_parameter.display_statement.argument = std::format("{0} {1}", operations[selected_subtype_index].display_name, bound);
		building_parameter.display_statement.argument_color = operations[selected_subtype_index].value_color;
	}
}

void DrawSubsetParameterTable(OutputEnvironment& output_environment) {
	ImGui::Text("Current subset parameters:");

	static bool column_color_enabled = false;
	ImGui::Checkbox("Enable column coloring", &column_color_enabled);

	ImVec2 outer_size = ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 10);
	const int kColumnCount = 5;
	const int kTableFlags =
		ImGuiTableFlags_Borders |
		ImGuiTableFlags_SizingFixedFit |
		ImGuiTableFlags_ScrollY;
	static int frozen_columns = 0;
	static int frozen_rows = 1;
	const float col_width = 50.0f;
	if (ImGui::BeginTable("table_results", kColumnCount, kTableFlags, outer_size)) {
		// prepare table header
		ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_WidthFixed, col_width);
		ImGui::TableSetupColumn("Group", ImGuiTableColumnFlags_WidthFixed, col_width);
		ImGui::TableSetupColumn("Column", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("", 
			ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoHeaderLabel |
			ImGuiTableColumnFlags_NoHeaderWidth, col_width);
		ImGui::TableSetupScrollFreeze(frozen_columns, frozen_rows);

		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
		for (int column = 0; column < kColumnCount; column++) {
			ImGui::TableSetColumnIndex(column);
			const char* column_name = ImGui::TableGetColumnName(column);
			ImGui::TableHeader(column_name);
		}



		// print parameters
		int parameter_count = 0;
		for (int group_index = 0; group_index < output_environment.subset_parameters.GetGroupCount(); group_index++) {
			std::vector<QueryParameter>& parameter_group = output_environment.subset_parameters.parameter_groups[group_index];
			for (int parameter_index = 0; parameter_index < parameter_group.size(); parameter_index++) {
				QueryParameter& subset_parameter = parameter_group[parameter_index];
				ImGui::TableNextRow();

				ImGui::TableSetColumnIndex(0);
				ImGui::Text(std::to_string(++parameter_count).c_str());

				ImGui::TableSetColumnIndex(1);
				if (column_color_enabled) {
					std::vector<ImVec4> group_colors = output_environment.subset_parameters.group_colors;
					ImU32 cell_bg_color = ImGui::GetColorU32(group_colors[group_index % group_colors.size()]);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				int displayed_group_index = group_index + 1;
				ImGui::Text(std::to_string(displayed_group_index).c_str());

				ImGui::TableSetColumnIndex(2);
				if (column_color_enabled) {
					ImU32 cell_bg_color = ImGui::GetColorU32(subset_parameter.display_statement.parameter_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				ImGui::Text(subset_parameter.display_statement.GetParameterName().c_str());

				ImGui::TableSetColumnIndex(3);
				if (column_color_enabled) {
					ImU32 cell_bg_color = ImGui::GetColorU32(subset_parameter.display_statement.argument_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				ImGui::Text(subset_parameter.display_statement.GetArgumentName().c_str());

				ImGui::TableSetColumnIndex(4);
				std::string button_id = "##Remove" + std::to_string(group_index) + ":" + std::to_string(parameter_index);
				ImGui::PushID(button_id.c_str());
				std::string label = "X";
				if (ImGui::SmallButton(label.c_str())) {
					output_environment.subset_parameters.RemoveParameter(group_index, parameter_index);
				}
				ImGui::PopID();
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

	/*
	std::vector<ValueType> value_types = {kAverageValue, kMinimumValue};
	static int selected_value_index = 0;
	std::string selected_value_name = value_types[selected_value_index].display_name;
	if (ImGui::Button(selected_value_name.c_str())) {
		ImGui::OpenPopup("Select value type");
	}
	if (ImGui::BeginPopup("Select value type")) {
		for (int i = 0; i < value_types.size(); i++) {
			if (ImGui::Selectable(value_types[i].display_name.c_str())) {
				selected_value_index = i;
			}
		}
		ImGui::EndPopup();
	}

	ImGui::SameLine();

	static int selected_argument_index = 0;
	std::string selected_argument_name = value_types[selected_value_index].values[selected_argument_index].first;
	if (ImGui::Button(selected_argument_name.c_str())) {
		ImGui::OpenPopup("Select parameter argument");
	}
	if (ImGui::BeginPopup("Select parameter argument")) {
		for (int i = 0; i < value_types[selected_value_index].values.size(); i++) {
			if (ImGui::Selectable(value_types[selected_value_index].values[i].first.c_str())) {
				selected_argument_index = i;
			}
		}
		ImGui::EndPopup();
	}

	if (ImGui::Button("Calculate value")) {
		QueryParameter value_query;
			//value_types[selected_value_index].query_format,
			//value_types[selected_value_index].values[selected_argument_index].second,
			//value_types[selected_value_index].display_name,
			//value_types[selected_value_index].values[selected_argument_index].first
		//);
		output_environment.value_parameter = value_query;
		QuerySubtable(output_environment);
	}

	if (window_parameters.window_size.x == 0) {
		window_parameters.window_size.x = ImGui::GetWindowWidth();
	}
	if (window_parameters.window_size.y == 0) {
		window_parameters.window_size.y = ImGui::GetWindowHeight();
	}
	*/

	ImGui::End();
}

void DrawSetDisplayWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	// text line showing # of entries in subset
	std::string subset_size_text = "Subset Size: " + std::to_string(output_environment.subset_entries.size());
	ImGui::Text(subset_size_text.c_str());

	static SubsetColumnInfo result_num_col_info("Result #", "", true, false, 
		ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_PreferSortDescending, 
		NumberColumnId, 0);
	static SubsetColumnInfo name_col_info("Name", "pretty_name", true, false, ImGuiTableColumnFlags_WidthFixed, NameColumnId, 90.0f);
	static SubsetColumnInfo dex_col_info("Dex #", "dex_number", true, true, ImGuiTableColumnFlags_WidthFixed, DexColumnId, 0);
	static SubsetColumnInfo color_info("Color", "color", false, true, ImGuiTableColumnFlags_WidthFixed, ColorColumnId, 0);
	static SubsetColumnInfo shape_info("Shape", "shape", false, true, ImGuiTableColumnFlags_WidthFixed, ShapeColumnId, 0);
	static SubsetColumnInfo height_info("Height (m)", "height", false, true, ImGuiTableColumnFlags_WidthFixed, HeightColumnId, 0);
	static SubsetColumnInfo weight_info("Weight (kg)", "weight", false, true, ImGuiTableColumnFlags_WidthFixed, WeightColumnId, 0);
	static SubsetColumnInfo prim_type_info("Primary Type", "primary_type", false, true, ImGuiTableColumnFlags_WidthFixed, PrimaryTypeColumnId, 0);
	static SubsetColumnInfo sec_type_info("Secondary Type", "secondary_type", false, true, ImGuiTableColumnFlags_WidthFixed, SecondaryTypeColumnId, 0);

	static std::vector<SubsetColumnInfo> column_infos = {
		result_num_col_info,
		name_col_info, 
		dex_col_info,
		color_info,
		shape_info,
		height_info,
		weight_info,
		prim_type_info,
		sec_type_info
	};
	
	if (ImGui::Button("Column Toggles")) {
		ImGui::OpenPopup("column_toggle_popup");
	}

	if (ImGui::BeginPopup("column_toggle_popup")) {
		for (SubsetColumnInfo& col_info : column_infos) {
			if (col_info.togglable) {
				ImGui::Checkbox(col_info.display_name.c_str(), &col_info.enabled);
			}
		}
		ImGui::EndPopup();
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
	static ImGuiInputTextFlags flags = ImGuiInputFlags_None;
	static ImU8 subset_page = 0;

	std::vector<std::string> page_size_labels = {"None", "15", "30", "50", "100"};
	std::vector<int> page_sizes = {10000, 15, 30, 50, 100};
	static int selected_page_size_index = 0;
	static int page_size = page_sizes[0];

	ImGui::Text("Page size limit: ");
	ImGui::SameLine();
	if (ImGui::SmallButton(page_size_labels[selected_page_size_index].c_str())) {
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

	ImGui::Text("Set displayed page: ");
	ImGui::SameLine();
	ImU8 page_count = output_environment.subset_entries.size() / page_size;
	float page_text_width = 75.0f;
	ImGui::SetNextItemWidth(page_text_width);
	ImGui::InputScalar("##subset_table_page", ImGuiDataType_U8, &subset_page, inputs_step ? &u8_one : NULL, NULL, "%u", flags);
	if (subset_page > page_count) {
		subset_page = page_count;
	}

	// subset display table
	ImVec2 outer_size = ImVec2(0.0f,ImGui::GetTextLineHeightWithSpacing() * 16);
	const int kTableFlags = 
		ImGuiTableFlags_Sortable |
		ImGuiTableFlags_Reorderable |
		ImGuiTableFlags_Resizable |
		ImGuiTableFlags_Borders |
		ImGuiTableFlags_ScrollY |
		ImGuiTableFlags_ScrollX |
		ImGuiTableFlags_NoSavedSettings;
	static int frozen_columns = 1;
	static int frozen_rows = 1;
	if (ImGui::BeginTable("subset_entries", active_column_count, kTableFlags, outer_size)) {
		// column setup
		for (SubsetColumnInfo active_column : active_columns) {
			std::string col_name = active_column.display_name;
			int col_flags = active_column.column_flags;
			int col_id = active_column.column_id;
			float col_width = active_column.column_width;
			ImGui::TableSetupColumn(col_name.c_str(), col_flags, col_width, col_id);
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
				if (std::strcmp(ImGui::TableGetColumnName(), "Result #") == 0) {
					int displayed_index = subset_index + 1;
					ImGui::Text(std::to_string(displayed_index).c_str());
					continue;
				}
				ImGui::Text(subset_entry.GetData(active_column.query_name).c_str());
			}
		}
		ImGui::EndTable();
	}

	// display current page info
	int shown_page_index = subset_page + 1;
	int shown_page_count = page_count + 1;
	std::string curr_page_text = std::vformat("Page {0} of {1}", std::make_format_args(shown_page_index, shown_page_count));
	ImGui::Text(curr_page_text.c_str());

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