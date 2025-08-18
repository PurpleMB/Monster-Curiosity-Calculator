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
#include <misc/cpp/imgui_stdlib.h>

#include "app.h"
#include "database.h"
#include "mcc_structs.h"
#include "mcc_database_constants.h"
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

	static QueryParameter building_parameter;

	static int selected_parameter_index = 0;
	static int selected_operation_index = 0;
	static int selected_value_index = 0;

	std::string selected_parameter_name = parameter_types[selected_parameter_index]->display_name;
	ImGui::Text("Select parameter to filter by:");
	if (ImGui::Button(selected_parameter_name.c_str())) {
		ImGui::OpenPopup("Select parameter");
	}

	if (ImGui::BeginPopup("Select parameter")) {
		for (int i = 0; i < parameter_types.size(); i++) {
			if (ImGui::Selectable(parameter_types[i]->display_name.c_str())) {
				if (i != selected_parameter_index) {
					selected_operation_index = 0;
					selected_value_index = 0;
				}
				selected_parameter_index = i;
			}
		}
		ImGui::EndPopup();
	}
	ParameterType* selected_param = parameter_types[selected_parameter_index].get();
	building_parameter.SetParameterInfo(ColumnDisplayInfo(selected_param->display_name, selected_param->parameter_color));

	std::vector<ParameterOperation> operations = selected_param->operations;
	if (ImGui::Button(operations[selected_operation_index].display_name.c_str())) {
		ImGui::OpenPopup("##Select parameter operation");
	}

	if (ImGui::BeginPopup("##Select parameter operation")) {
		for (int i = 0; i < operations.size(); i++) {
			if (ImGui::Selectable(operations[i].display_name.c_str())) {
				selected_operation_index = i;
			}
		}
		ImGui::EndPopup();
	}
	ParameterOperation selected_operation = selected_param->operations[selected_operation_index];
	building_parameter.SetOperationInfo(ColumnDisplayInfo(selected_operation.display_name, selected_operation.value_color));


	EnumeratedParameterType enum_param;
	SliderEnumeratedParameterType slider_param;
	OpenParameterType open_param;
	IntegerParameterType int_param;
	DecimalParameterType dec_param;
	switch (parameter_types[selected_parameter_index]->GetParameterCategory()) {
		case Enumerated:
			enum_param = *dynamic_cast<EnumeratedParameterType*>(selected_param);
			DrawEnumeratorParameterSelector(enum_param, selected_operation, selected_value_index, building_parameter);
			break;
		case EnumeratedSlider:
			slider_param = * dynamic_cast<SliderEnumeratedParameterType*>(selected_param);
			DrawSliderParameterSelector(slider_param, selected_operation, selected_value_index, building_parameter);
			break;
		case Open:
			open_param = *dynamic_cast<OpenParameterType*>(selected_param);
			DrawOpenParameterSelector(open_param, selected_operation, building_parameter);
			break;
		case Integer:
			int_param = *dynamic_cast<IntegerParameterType*>(selected_param);
			DrawIntegerParameterSelector(int_param, selected_operation, building_parameter);
			break;
		case Decimal:
			dec_param = *dynamic_cast<DecimalParameterType*>(selected_param);
			DrawDecimalParameterSelector(dec_param, selected_operation, building_parameter);
			break;
		default:
			ImGui::SameLine();
			ImGui::Text("ERROR: UNDEFINED PARAMETER TYPE");
			break;
	}

	const ImU8 u8_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
	static ImU8 parameter_group = 1;

	if (parameter_group < 1) {
		parameter_group = 1;
	}
	if (parameter_group > output_environment.subset_parameters.GetGroupCount()) {
		parameter_group = output_environment.subset_parameters.GetGroupCount();
	}

	ImGui::Text("Set Parameter Group: ");
	ImGui::SameLine();
	ImGui::InputScalar("##parameter_group", ImGuiDataType_U8, &parameter_group, inputs_step ? &u8_one : NULL, NULL, "%u", flags);


	if (ImGui::Button("Apply Parameter")) {
		output_environment.subset_parameters.AddParameter(building_parameter, (parameter_group - 1));
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

void DrawEnumeratorParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter) {
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
	ParameterValue selected_value = param_type.values[selected_value_index];
	building_parameter.SetValueInfo(ColumnDisplayInfo(selected_value.display_name, selected_value.value_color));

	std::string formatted_operation = std::vformat(operation.database_name, std::make_format_args(selected_value.database_name));
	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawSliderParameterSelector(SliderEnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter) {
	std::string user_prompt = std::vformat("Set {0}", std::make_format_args(operation.operands[0]));
	ImGui::Text(user_prompt.c_str());
	
	std::string selected_value_name = param_type.values[selected_value_index].display_name;
	int options_count = param_type.values.size();
	ImGui::SliderInt("", &selected_value_index, 0, options_count - 1, selected_value_name.c_str());

	ParameterValue selected_value = param_type.values[selected_value_index];
	building_parameter.SetValueInfo(ColumnDisplayInfo(selected_value.display_name, selected_value.value_color));

	std::string formatted_operation = std::vformat(operation.database_name, std::make_format_args(selected_value.database_name));
	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawOpenParameterSelector(OpenParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter) {
	std::string operand = operation.operands[0];
	std::string label = std::vformat("Set {0}:", std::make_format_args(operand));
	ImGui::Text(label.c_str());
	ImGui::SameLine();

	std::string input_label = "##text_value_input";
	static std::string value_text = "";
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_EscapeClearsAll;
	ImGui::InputText(input_label.c_str(), &value_text, flags);

	building_parameter.SetValueInfo(ColumnDisplayInfo(value_text, DisplayColor()));

	std::string formatted_operation = std::vformat(operation.database_name, std::make_format_args(value_text));
	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawIntegerParameterSelector(IntegerParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter) {
	int min_val = param_type.min_value;
	int max_val = param_type.max_value;

	const int u32_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EscapeClearsAll;
	static std::vector<int> operand_values = {0, 0};

	int operand_count = operation.operands.size();
	for (int operand_index = 0; operand_index < operand_count; operand_index++) {
		while (operand_index >= operand_values.size()) {
			operand_values.push_back(0);
		}

		std::string operand = operation.operands[operand_index];
		std::string label = std::vformat("Set {0}:", std::make_format_args(operand, operand_index));
		ImGui::Text(label.c_str());
		ImGui::SameLine();
		std::string input_label = std::vformat("##operand_{0}", std::make_format_args(operand_index));
		ImGui::InputScalar(input_label.c_str(), ImGuiDataType_U32, &operand_values[operand_index], inputs_step ? &u32_one : NULL, NULL, "%u", flags);
	}

	std::string operation_format = operation.database_name;
	std::string formatted_operation;
	std::string formatted_display;
	if (operand_count == 1) {
		formatted_operation = std::vformat(operation_format, std::make_format_args(operand_values[0]));
		formatted_display = std::vformat("{0}", std::make_format_args(operand_values[0]));
	}
	else if (operand_count == 2) {
		formatted_operation = std::vformat(operation_format, std::make_format_args(operand_values[0], operand_values[1]));
		formatted_display = std::vformat("[{0}, {1}]", std::make_format_args(operand_values[0], operand_values[1]));
	}

	building_parameter.SetValueInfo(ColumnDisplayInfo(formatted_display, DisplayColor()));

	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawDecimalParameterSelector(DecimalParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter) {
	double min_val = param_type.min_value;
	double max_val = param_type.max_value;

	const double f64_one = 1.0;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EscapeClearsAll;
	static std::vector<double> operand_values = {0, 0};

	int operand_count = operation.operands.size();
	for (int operand_index = 0; operand_index < operand_count; operand_index++) {
		while (operand_index >= operand_values.size()) {
			operand_values.push_back(0);
		}

		std::string operand = operation.operands[operand_index];
		std::string label = std::vformat("Set {0}:", std::make_format_args(operand, operand_index));
		ImGui::Text(label.c_str());
		ImGui::SameLine();
		std::string input_label = std::vformat("##operand_{0}", std::make_format_args(operand_index));
		ImGui::InputScalar(input_label.c_str(), ImGuiDataType_Double, &operand_values[operand_index], inputs_step ? &f64_one : NULL, NULL, NULL, flags);
	}

	std::string operation_format = operation.database_name;
	std::string formatted_operation;
	std::string formatted_display;
	if (operand_count == 1) {
		formatted_operation = std::vformat(operation_format, std::make_format_args(operand_values[0]));
		formatted_display = std::vformat("{0}", std::make_format_args(operand_values[0]));
	}
	else if (operand_count == 2) {
		formatted_operation = std::vformat(operation_format, std::make_format_args(operand_values[0], operand_values[1]));
		formatted_display = std::vformat("[{0}, {1}]", std::make_format_args(operand_values[0], operand_values[1]));
	}

	building_parameter.SetValueInfo(ColumnDisplayInfo(formatted_display, DisplayColor()));

	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawSubsetParameterTable(OutputEnvironment& output_environment) {
	ImGui::Text("Current subset parameters:");

	static bool group_color_enabled = false;
	static bool parameter_color_enabled = false;
	static bool operation_color_enabled = false;
	static bool value_color_enabled = false;
	static std::vector<bool*> column_color_toggles = {&group_color_enabled, &parameter_color_enabled, &operation_color_enabled, &value_color_enabled};
	static std::vector<std::string> column_toggle_names = {"Parameter Group", "Parameter", "Operation", "Value"};
	if (ImGui::Button("Column Coloring Toggles")) {
		ImGui::OpenPopup("column_color_popup");
	}

	if (ImGui::BeginPopup("column_color_popup")) {
		for (int i = 0; i < column_color_toggles.size(); i++) {
			ImGui::Checkbox(column_toggle_names[i].c_str(), column_color_toggles[i]);
		}
		ImGui::EndPopup();
	}

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
		ImGui::TableSetupColumn("Group", ImGuiTableColumnFlags_WidthFixed, col_width);
		ImGui::TableSetupColumn("Parameter", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn("Operation", ImGuiTableColumnFlags_WidthStretch);
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
				if (group_color_enabled) {
					ImVec4 group_cell_color = output_environment.subset_parameters.GetGroupColor(group_index);
					ImU32 cell_bg_color = ImGui::GetColorU32(group_cell_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				int displayed_group_index = group_index + 1;
				ImGui::Text(std::to_string(displayed_group_index).c_str());

				ImGui::TableSetColumnIndex(1);
				ColumnDisplayInfo parameter_column_info = subset_parameter.GetParameterDisplayInfo();
				if (parameter_color_enabled) {
					ImVec4 param_cell_color = parameter_column_info.GetColor().GetColorValues();
					ImU32 cell_bg_color = ImGui::GetColorU32(param_cell_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				ImGui::Text(parameter_column_info.GetText().c_str());

				ImGui::TableSetColumnIndex(2);
				ColumnDisplayInfo operation_column_info = subset_parameter.GetOperationDisplayInfo();
				if (operation_color_enabled) {
					ImVec4 param_cell_color = operation_column_info.GetColor().GetColorValues();
					ImU32 cell_bg_color = ImGui::GetColorU32(param_cell_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				ImGui::Text(operation_column_info.GetText().c_str());

				ImGui::TableSetColumnIndex(3);
				ColumnDisplayInfo value_column_info = subset_parameter.GetValueDisplayInfo();
				if (value_color_enabled) {
					ImVec4 param_cell_color = value_column_info.GetColor().GetColorValues();
					ImU32 cell_bg_color = ImGui::GetColorU32(param_cell_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				ImGui::Text(value_column_info.GetText().c_str());

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

void DrawSetDisplayWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment, std::vector<ColumnStatus>& column_statuses) {
	ImGui::SetNextWindowSize(window_parameters.window_size);
	ImGui::SetNextWindowPos(window_parameters.window_position);

	ImGui::Begin(window_parameters.name.c_str(), nullptr, window_parameters.imgui_window_settings);

	// text line showing # of entries in subset
	std::string subset_size_text = "Subset Size: " + std::to_string(output_environment.subset_entries.size());
	ImGui::Text(subset_size_text.c_str());
	
	if (ImGui::Button("Column Toggles")) {
		ImGui::OpenPopup("column_toggle_popup");
	}

	if (ImGui::BeginPopup("column_toggle_popup")) {
		for (ColumnStatus& col : column_statuses) {
			if (col.GetColumnInfo().togglable) {
				ImGui::Checkbox(col.GetColumnInfo().display_name.c_str(), &col.enabled);
			}
		}
		ImGui::EndPopup();
	}

	std::vector<ColumnInfo> active_columns = {};
	for (ColumnStatus col : column_statuses) {
		if (col.enabled) {
			active_columns.push_back(col.GetColumnInfo());
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
		for (ColumnInfo active_column : active_columns) {
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
			for (ColumnInfo active_column : active_columns) {
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