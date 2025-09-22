#pragma once

#define NOMINMAX

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

#include "mcc_display_structs.h"
#include "mcc_parameter_structs.h"
#include "mcc_value_structs.h"
#include "mcc_subset_structs.h"
#include "mcc_communication_structs.h"

#include "mcc_database_constants.h"
#include "mcc_database_querying.h"
#include "mcc_menu_elements.h"

#include "mcc_gui_windows.h"


namespace monster_calculator {

void DrawMenuBarWindow(OutputEnvironment& output_environment) {
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Menu")) {
			DrawMenuBarMenu(output_environment);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools")) {
			DrawMenuBarTools(output_environment);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			DrawMenuBarHelp(output_environment);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void DrawSetParameterWindow(OutputEnvironment& output_environment,
	std::vector<std::shared_ptr<ParameterType>> parameter_types, ParameterTypeConverter param_converter) {
	static QueryParameter building_parameter;

	static int selected_parameter_index = 0;
	static int selected_operation_index = 0;
	static int selected_value_index = 0;

	std::string selected_parameter_name = parameter_types[selected_parameter_index]->display_name;
	ImGui::Text("Define parameters to refine data set:");
	ImGui::NewLine();

	static const ImVec2 combo_size = ImVec2(175, 0);

	static ImGuiComboFlags param_combo_flags = 0;
	ImGui::SetNextItemWidth(combo_size.x);
	if (ImGui::BeginCombo("Subset Parameter Type", selected_parameter_name.c_str(), param_combo_flags)) {
		for (int i = 0; i < parameter_types.size(); i++) {
			const bool is_selected = (selected_parameter_index == i);
			if (ImGui::Selectable(parameter_types[i]->display_name.c_str(), is_selected)) {
				std::vector<ParameterOperation> curr_ops = parameter_types[selected_parameter_index]->operations;
				std::vector<ParameterOperation> incoming_ops = parameter_types[i]->operations;
				if (incoming_ops != curr_ops) {
					selected_operation_index = 0;
				}
				selected_parameter_index = i;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ParameterType* selected_param = parameter_types[selected_parameter_index].get();
	building_parameter.SetParameterInfo(TableCellDisplayInfo(selected_param->display_name, selected_param->parameter_color));

	std::vector<ParameterOperation> operations = selected_param->operations;
	if (operations.size() > 1) {
		static  ImGuiComboFlags oper_combo_flags = 0;
		ImGui::SetNextItemWidth(combo_size.x);
		if (ImGui::BeginCombo("Subset Parameter Operation", operations[selected_operation_index].display_name.c_str(), oper_combo_flags)) {
			for (int i = 0; i < operations.size(); i++) {
				const bool is_selected = (selected_operation_index == i);
				if (ImGui::Selectable(operations[i].display_name.c_str(), is_selected)) {
					selected_operation_index = i;
				}

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
	}

	ParameterOperation selected_operation = selected_param->operations[selected_operation_index];
	building_parameter.SetOperationInfo(TableCellDisplayInfo(selected_operation.display_name, selected_operation.value_color));


	EnumeratedParameterType enum_param;
	PreferredEnumDisplay display_method;
	OpenParameterType open_param;
	IntegerParameterType int_param;
	DecimalParameterType dec_param;
	switch (parameter_types[selected_parameter_index]->GetParameterCategory()) {
		case Enumerated:
			enum_param = *dynamic_cast<EnumeratedParameterType*>(selected_param);
			display_method = enum_param.GetPreferredDisplay();
			switch (display_method) {
				case Slider:
					DrawSliderParameterSelector(enum_param, selected_operation, selected_value_index, building_parameter);
					break;
				case ButtonGrid:
					DrawButtonGridParameterSelector(enum_param, selected_operation, selected_value_index, building_parameter);
					break;
				case ImageButtonGrid:
					DrawImageButtonGridParameterSelector(enum_param, selected_operation, selected_value_index, building_parameter, output_environment);
					break;
				case Dropdown:
					DrawDropdownParameterSelector(enum_param, selected_operation, selected_value_index, building_parameter);
					break;
			}
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

	static int parameter_group = 0;
	int parameter_group_count = output_environment.subset_parameters.GetGroupCount();
	if (parameter_group_count > 1) {
		DrawParameterGroupSelector(parameter_group, output_environment.subset_parameters.GetGroupNameList());
	}
	if (ImGui::Button("Apply Parameter")) {
		output_environment.subset_parameters.AddParameter(building_parameter, parameter_group);
	}

	ImGui::Separator();


	DrawSubsetParameterTable(output_environment);

	if (ImGui::Button("Find Matching Monsters")) {
		GenerateTableSubset(output_environment, kMainTableName, kSubTableName);
		RetrieveTableEntries(output_environment, kSubTableName);
		output_environment.ConvertSubsetEntries(param_converter);
	}

	ImGui::SameLine();
	if (ImGui::Button("Clear All Parameters")) {
		output_environment.subset_parameters.ClearAllParameters();
	}
}

void DrawDropdownParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter) {
	std::string selected_value_name = param_type.values[selected_value_index].display_name;

	static const ImVec2 combo_size = ImVec2(200, 0);
	static ImGuiComboFlags value_combo_flags = 0;
	ImGui::SetNextItemWidth(combo_size.x);
	if (ImGui::BeginCombo("Subset Parameter Value", selected_value_name.c_str(), value_combo_flags)) {
		for (int i = 0; i < param_type.values.size(); i++) {
			const bool is_selected = (selected_value_index == i);
			if (ImGui::Selectable(param_type.values[i].display_name.c_str(), is_selected)) {
				selected_value_index = i;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ParameterValue selected_value = param_type.values[selected_value_index];
	building_parameter.SetValueInfo(TableCellDisplayInfo(selected_value.display_name, selected_value.value_color));

	std::string formatted_operation = std::vformat(operation.database_name, std::make_format_args(selected_value.database_name));
	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawSliderParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter) {
	std::string user_prompt = std::vformat("Set {0}", std::make_format_args(operation.operands[0]));
	ImGui::Text(user_prompt.c_str());
	
	std::string selected_value_name = param_type.values[selected_value_index].display_name;
	int options_count = param_type.values.size();
	ImGui::SliderInt("", &selected_value_index, 0, options_count - 1, selected_value_name.c_str());

	ParameterValue selected_value = param_type.values[selected_value_index];
	building_parameter.SetValueInfo(TableCellDisplayInfo(selected_value.display_name, selected_value.value_color));

	std::string formatted_operation = std::vformat(operation.database_name, std::make_format_args(selected_value.database_name));
	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawButtonGridParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter) {
	std::string selected_value_name = param_type.values[selected_value_index].display_name;
	std::string current_value_indicator = std::vformat("Currently selected value: {0}", std::make_format_args(selected_value_name));
	ImGui::Text(current_value_indicator.c_str());

	ImVec2 button_size = param_type.GetButtonSize();
	int buttons_per_row = param_type.GetButtonsPerRow();
	for (int i = 0; i < param_type.values.size(); i++) {
		if (i % buttons_per_row != 0) {
			ImGui::SameLine();
		}
		if (ImGui::Button(param_type.values[i].display_name.c_str(), button_size)) {
			selected_value_index = i;
		}
		
	}

	ParameterValue selected_value = param_type.values[selected_value_index];
	building_parameter.SetValueInfo(TableCellDisplayInfo(selected_value.display_name, selected_value.value_color));

	std::string formatted_operation = std::vformat(operation.database_name, std::make_format_args(selected_value.database_name));
	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawImageButtonGridParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter, OutputEnvironment& output_environment) {
	std::string selected_value_name = param_type.values[selected_value_index].display_name;
	std::string current_value_indicator = std::vformat("Currently selected value: {0}", std::make_format_args(selected_value_name));
	ImGui::Text(current_value_indicator.c_str());

	ImVec2 button_size = param_type.GetButtonSize();
	int buttons_per_row = param_type.GetButtonsPerRow();
	for (int i = 0; i < param_type.values.size(); i++) {
		std::string button_label = param_type.values[i].display_name;
		ImTextureID button_tex = output_environment.GetTextureFromMap(param_type.values[i].database_name);
		if (i % buttons_per_row != 0) {
			ImGui::SameLine();
		}
		if (ImGui::ImageButton(button_label.c_str(), button_tex, param_type.GetButtonSize())) {
			selected_value_index = i;
		}
	}

	ParameterValue selected_value = param_type.values[selected_value_index];
	building_parameter.SetValueInfo(TableCellDisplayInfo(selected_value.display_name, selected_value.value_color));

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

	ParameterValue temp_val = ParameterValue(value_text);
	param_type.SetValueColorForType(temp_val);
	building_parameter.SetValueInfo(TableCellDisplayInfo(value_text, temp_val.value_color));

	std::string formatted_operation = std::vformat(operation.database_name, std::make_format_args(value_text));
	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawIntegerParameterSelector(IntegerParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter) {
	int min_val = param_type.min_value;
	int max_val = param_type.max_value;

	const int u32_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EscapeClearsAll
		| ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_ParseEmptyRefVal;
	static std::vector<int> operand_values = {min_val, max_val};

	int operand_count = operation.operands.size();
	for (int operand_index = 0; operand_index < operand_count; operand_index++) {
		std::string operand = operation.operands[operand_index];
		std::string label = std::vformat("Set {0}:", std::make_format_args(operand, operand_index));
		ImGui::Text(label.c_str());
		ImGui::SameLine();
		int input_field_width = 100;
		ImGui::SetNextItemWidth(input_field_width);
		std::string input_label = std::vformat("##operand_{0}", std::make_format_args(operand_index));
		ImGui::InputScalar(input_label.c_str(), ImGuiDataType_U32, &operand_values[operand_index], inputs_step ? &u32_one : NULL, NULL, "%u", flags);

		ImGui::SameLine();
		int slider_width = 250;
		ImGui::SetNextItemWidth(slider_width);
		std::string slider_label = std::vformat("##slider_{0}", std::make_format_args(operand_index));
		ImGui::SliderInt(slider_label.c_str(), &operand_values[operand_index], min_val, max_val, "");
	}

	std::string operation_format = operation.database_name;
	std::string formatted_operation;
	std::string formatted_display;
	ParameterValue temp_val;
	if (operand_count == 1) {
		operand_values[0] = std::clamp(operand_values[0], min_val, max_val);
		formatted_operation = std::vformat(operation_format, std::make_format_args(operand_values[0]));
		formatted_display = std::vformat("{0}", std::make_format_args(operand_values[0]));
		temp_val = ParameterValue(std::to_string(operand_values[0]));
	}
	else if (operand_count == 2) {
		operand_values[0] = std::clamp(operand_values[0], min_val, std::min(max_val, operand_values[1]));
		operand_values[1] = std::clamp(operand_values[1], std::max(operand_values[0], min_val), max_val);
		formatted_operation = std::vformat(operation_format, std::make_format_args(operand_values[0], operand_values[1]));
		formatted_display = std::vformat("[{0}, {1}]", std::make_format_args(operand_values[0], operand_values[1]));
		temp_val = ParameterValue(std::to_string((operand_values[0] + operand_values[1]) / 2));
	}

	
	param_type.SetValueColorForType(temp_val);
	building_parameter.SetValueInfo(TableCellDisplayInfo(formatted_display, temp_val.value_color));

	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawDecimalParameterSelector(DecimalParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter) {
	double min_val = param_type.min_value;
	double max_val = param_type.max_value;

	const double f64_one = 1.0;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EscapeClearsAll
		| ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_ParseEmptyRefVal;
	static std::vector<double> operand_values = {min_val, max_val};

	int operand_count = operation.operands.size();
	for (int operand_index = 0; operand_index < operand_count; operand_index++) {
		std::string operand = operation.operands[operand_index];
		std::string label = std::vformat("Set {0}:", std::make_format_args(operand, operand_index));
		ImGui::Text(label.c_str());
		ImGui::SameLine();
		int input_field_width = 100;
		ImGui::SetNextItemWidth(input_field_width);
		std::string input_label = std::vformat("##operand_{0}", std::make_format_args(operand_index));
		ImGui::InputScalar(input_label.c_str(), ImGuiDataType_Double, &operand_values[operand_index], inputs_step ? &f64_one : NULL, NULL, "%.1f", flags);

		ImGui::SameLine();
		int slider_width = 250;
		ImGui::SetNextItemWidth(slider_width);
		std::string slider_label = std::vformat("##slider_{0}", std::make_format_args(operand_index));
		ImGui::SliderScalar(slider_label.c_str(), ImGuiDataType_Double, &operand_values[operand_index], &min_val, &max_val, "##%.1f");
	}

	std::string operation_format = operation.database_name;
	std::string formatted_operation;
	std::string formatted_display;
	ParameterValue temp_val;
	if (operand_count == 1) {
		operand_values[0] = std::clamp(operand_values[0], min_val, max_val);
		formatted_operation = std::vformat(operation_format, std::make_format_args(operand_values[0]));
		formatted_display = std::vformat("{0}", std::make_format_args(operand_values[0]));
		temp_val = ParameterValue(std::to_string(operand_values[0]));
	}
	else if (operand_count == 2) {
		operand_values[0] = std::clamp(operand_values[0], min_val, std::min(max_val, operand_values[1]));
		operand_values[1] = std::clamp(operand_values[1], std::max(operand_values[0], min_val), max_val);
		formatted_operation = std::vformat(operation_format, std::make_format_args(operand_values[0], operand_values[1]));
		formatted_display = std::vformat("[{0}, {1}]", std::make_format_args(operand_values[0], operand_values[1]));
		temp_val = ParameterValue(std::to_string((operand_values[0] + operand_values[1]) / 2.0f));
	}

	param_type.SetValueColorForType(temp_val);
	building_parameter.SetValueInfo(TableCellDisplayInfo(formatted_display, temp_val.value_color));

	std::string formatted_query = std::vformat(param_type.database_format, std::make_format_args(formatted_operation));
	building_parameter.SetQuery(formatted_query);
}

void DrawParameterGroupSelector(int& parameter_group_index, std::vector<std::string> parameter_group_names_list) {
	std::string selected_group_name = parameter_group_names_list[parameter_group_index];
	static const ImVec2 combo_size = ImVec2(200, 0);
	static ImGuiComboFlags group_combo_flags = 0;
	ImGui::SetNextItemWidth(combo_size.x);
	if (ImGui::BeginCombo("Subset Parameter Group", selected_group_name.c_str(), group_combo_flags)) {
		for (int i = 0; i < parameter_group_names_list.size(); i++) {
			const bool is_selected = (parameter_group_index == i);
			if (ImGui::Selectable(parameter_group_names_list[i].c_str(), is_selected)) {
				parameter_group_index = i;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

void DrawSubsetParameterTable(OutputEnvironment& output_environment) {
	ImGui::Text("Current subset parameters:");

	static bool group_color_enabled = false;
	static bool parameter_color_enabled = false;
	static bool operation_color_enabled = false;
	static bool value_color_enabled = false;
	static std::vector<bool*> column_color_toggles = {&group_color_enabled, &parameter_color_enabled, &operation_color_enabled, &value_color_enabled};
	static std::vector<std::string> column_toggle_names = {"Parameter Group", "Parameter", "Operation", "Value"};


	// edit icon button
	ImGui::SameLine();
	std::string button_label = "Parameter Table Options";
	ImTextureID button_tex = output_environment.GetTextureFromMap("edit");
	float line_height = ImGui::GetTextLineHeight();
	if (ImGui::ImageButton(button_label.c_str(), button_tex, ImVec2(line_height, line_height))) {
		ImGui::OpenPopup("table_options_popup");
	}
	if (ImGui::BeginPopup("table_options_popup")) {
		if (ImGui::BeginMenu("Coloring Options")) {
			for (int i = 0; i < column_color_toggles.size(); i++) {
				ImGui::Checkbox(column_toggle_names[i].c_str(), column_color_toggles[i]);
			}
			ImGui::EndMenu();
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
					DisplayColor group_color = output_environment.subset_parameters.GetGroupDisplayColor(group_index);
					ImVec4 cell_color = group_color.EvaluateColorWithIntensity(output_environment.table_color_intensity);
					ImU32 cell_bg_color = ImGui::GetColorU32(cell_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}

				std::string group_name = output_environment.subset_parameters.GetGroupName(group_index);
				ImGui::Text(group_name.c_str());

				ImGui::TableSetColumnIndex(1);
				TableCellDisplayInfo parameter_column_info = subset_parameter.GetParameterDisplayInfo();
				if (parameter_color_enabled) {
					DisplayColor param_color = parameter_column_info.GetDisplayColor();
					ImVec4 cell_color = param_color.EvaluateColorWithIntensity(output_environment.table_color_intensity);
					ImU32 cell_bg_color = ImGui::GetColorU32(cell_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				ImGui::Text(parameter_column_info.GetText().c_str());

				ImGui::TableSetColumnIndex(2);
				TableCellDisplayInfo operation_column_info = subset_parameter.GetOperationDisplayInfo();
				if (operation_color_enabled) {
					DisplayColor oper_color = operation_column_info.GetDisplayColor();
					ImVec4 cell_color = oper_color.EvaluateColorWithIntensity(output_environment.table_color_intensity);
					ImU32 cell_bg_color = ImGui::GetColorU32(cell_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				ImGui::Text(operation_column_info.GetText().c_str());

				ImGui::TableSetColumnIndex(3);
				TableCellDisplayInfo value_column_info = subset_parameter.GetValueDisplayInfo();
				if (value_color_enabled) {
					DisplayColor value_color = value_column_info.GetDisplayColor();
					ImVec4 cell_color = value_color.EvaluateColorWithIntensity(output_environment.table_color_intensity);
					ImU32 cell_bg_color = ImGui::GetColorU32(cell_color);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
				}
				ImGui::Text(value_column_info.GetText().c_str());

				ImGui::TableSetColumnIndex(4);
				std::string button_id = "##Remove" + std::to_string(group_index) + ":" + std::to_string(parameter_index);
				ImGui::PushID(button_id.c_str());
				ImTextureID button_tex = output_environment.GetTextureFromMap("remove");
				float line_height = ImGui::GetTextLineHeight();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
				if (ImGui::ImageButton(button_id.c_str(), button_tex, ImVec2(line_height, line_height))) {
					output_environment.subset_parameters.RemoveParameter(group_index, parameter_index);
				}
				ImGui::PopStyleVar();
				ImGui::PopID();
			}
		}
		ImGui::EndTable();
	}
}

void DrawValueParameterWindow(OutputEnvironment& output_environment, std::vector<std::shared_ptr<ValueOperation>> value_operations, ParameterTypeConverter param_converter) {
	static int selected_operation_index = 0;
	std::string selected_operation_name = value_operations[selected_operation_index]->GetDisplayName();
	static int selected_arg_index = 0;

	ImGui::Text("Select value to calculate:");

	ImGui::Text("Subset ");
	
	ImGui::SameLine();
	static ImGuiComboFlags oper_combo_flags = 0;
	static const ImVec2 oper_combo_size = ImVec2(125, 0);
	ImGui::SetNextItemWidth(oper_combo_size.x);
	if (ImGui::BeginCombo("##select_operation", selected_operation_name.c_str(), oper_combo_flags)) {
		for (int i = 0; i < value_operations.size(); i++) {
			const bool is_selected = (selected_operation_index == i);
			if (ImGui::Selectable(value_operations[i]->GetDisplayName().c_str(), is_selected)) {
				std::vector<ValueOperationArgument> curr_args = value_operations[selected_operation_index]->GetArgumentList();
				std::vector<ValueOperationArgument> incoming_args = value_operations[i]->GetArgumentList();
				if (incoming_args != curr_args) {
					selected_arg_index = 0;
				}
				selected_operation_index = i;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::SameLine();
	ImGui::Text(" of ");

	std::vector<ValueOperationArgument> arguments = value_operations[selected_operation_index]->GetArgumentList();
	std::string selected_arg_name = arguments[selected_arg_index].display_name;

	ImGui::SameLine();
	static ImGuiComboFlags arg_combo_flags = 0;
	static const ImVec2 arg_combo_size = ImVec2(175, 0);
	ImGui::SetNextItemWidth(arg_combo_size.x);
	if (ImGui::BeginCombo("##select_argument", selected_arg_name.c_str(), arg_combo_flags)) {
		for (int i = 0; i < arguments.size(); i++) {
			const bool is_selected = (selected_arg_index == i);
			if (ImGui::Selectable(arguments[i].display_name.c_str(), is_selected)) {
				selected_arg_index = i;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	if (ImGui::Button("Add Value Operation")) {
		ValueOperation selected_operation = *value_operations[selected_operation_index].get();
		ValueOperationArgument selected_argument = selected_operation.GetArgumentList()[selected_arg_index];

		ValueQuery subset_value_query = ValueQuery(selected_operation, selected_argument);

		output_environment.value_queries.push_back(subset_value_query);
	}

	ImGui::Separator();

	DrawValueOperationTable(output_environment);

	if (ImGui::Button("Calculate Unlocked Values")) {
		std::vector<int> active_query_indices = output_environment.GetUnlockedValueQueryIndices();
		std::string value_set_query = output_environment.GenerateValueQuerySetText(active_query_indices, kSubTableName);

		QueryValuesFromTable(output_environment, kSubTableName, active_query_indices, value_set_query);
		output_environment.ConvertValueQueryResults(param_converter);
	}
}

void DrawValueOperationTable(OutputEnvironment& output_environment) {
	static bool operation_color_enabled = false;
	static bool argument_color_enabled = false;
	static bool result_color_enabled = false;
	static std::vector<bool*> column_color_toggles = {&operation_color_enabled, &argument_color_enabled,  &result_color_enabled};
	static std::vector<std::string> column_toggle_names = {"Operation", "Argument", "Result"};

	// edit icon button
	ImGui::SameLine();
	std::string button_label = "Value Table Options";
	ImTextureID button_tex = output_environment.GetTextureFromMap("edit");
	float line_height = ImGui::GetTextLineHeight();
	if (ImGui::ImageButton(button_label.c_str(), button_tex, ImVec2(line_height, line_height))) {
		ImGui::OpenPopup("table_options_popup");
	}
	if (ImGui::BeginPopup("table_options_popup")) {
		if (ImGui::BeginMenu("Coloring Options")) {
			for (int i = 0; i < column_color_toggles.size(); i++) {
				ImGui::Checkbox(column_toggle_names[i].c_str(), column_color_toggles[i]);
			}
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}

	ImGui::Text("Current subset value operations:");

	ImVec2 outer_size = ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 10);
	const int kColumnCount = 4;
	const int kTableFlags =
		ImGuiTableFlags_Borders |
		ImGuiTableFlags_SizingFixedFit |
		ImGuiTableFlags_ScrollY;
	static int frozen_columns = 0;
	static int frozen_rows = 1;
	const float col_width = 50.0f;
	if (ImGui::BeginTable("table_results", kColumnCount, kTableFlags, outer_size)) {
		// prepare table header
		ImGui::TableSetupColumn("Operation", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn("Argument", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn("Result", ImGuiTableColumnFlags_WidthStretch);
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

		// print operations
		for (int operation_index = 0; operation_index < output_environment.value_queries.size(); operation_index++) {
			ValueQuery& value_query = output_environment.value_queries[operation_index];
			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);
			if (operation_color_enabled) {
				DisplayColor operation_color = value_query.GetOperationDisplayInfo().GetDisplayColor();
				ImVec4 cell_color = operation_color.EvaluateColorWithIntensity(output_environment.table_color_intensity);
				ImU32 cell_bg_color = ImGui::GetColorU32(cell_color);
				ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
			}
			TableCellDisplayInfo operation_info = value_query.GetOperationDisplayInfo();
			ImGui::Text(operation_info.GetText().c_str());

			ImGui::TableSetColumnIndex(1);
			if (argument_color_enabled) {
				DisplayColor argument_color = value_query.GetArgumentDisplayInfo().GetDisplayColor();
				ImVec4 cell_color = argument_color.EvaluateColorWithIntensity(output_environment.table_color_intensity);
				ImU32 cell_bg_color = ImGui::GetColorU32(cell_color);
				ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
			}
			TableCellDisplayInfo argument_info = value_query.GetArgumentDisplayInfo();
			ImGui::Text(argument_info.GetText().c_str());

			ImGui::TableSetColumnIndex(2);
			if (result_color_enabled) {
				DisplayColor result_color = value_query.GetResultDisplayInfo().GetDisplayColor();
				ImVec4 cell_color = result_color.EvaluateColorWithIntensity(output_environment.table_color_intensity);
				ImU32 cell_bg_color = ImGui::GetColorU32(cell_color);
				ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
			}
			TableCellDisplayInfo result_info = value_query.GetResultDisplayInfo();
			ImGui::Text(result_info.GetText().c_str());

			ImGui::TableSetColumnIndex(3);
			ValueQuery& curr_query = output_environment.value_queries[operation_index];
			// value locking buttons
			std::string lock_id = "##LockOperation" + std::to_string(operation_index);
			ImGui::PushID(lock_id.c_str());
			if (curr_query.IsLocked()) {
				if (ImGui::SmallButton("Unlock Value")) {
					curr_query.SetLocked(false);
				}
			}
			else {
				if (ImGui::SmallButton("Lock Value")) {
					curr_query.SetLocked(true);
				}
			}
			ImGui::PopID();
			// remove button
			std::string remove_id = "##RemoveOperation" + std::to_string(operation_index);
			ImGui::PushID(remove_id.c_str());
			ImTextureID button_tex = output_environment.GetTextureFromMap("remove");
			float line_height = ImGui::GetTextLineHeight();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			if (ImGui::ImageButton(remove_id.c_str(), button_tex, ImVec2(line_height, line_height))) {
				output_environment.value_queries.erase(output_environment.value_queries.begin() + operation_index);
			}
			ImGui::PopStyleVar();
			ImGui::PopID();
		}
		ImGui::EndTable();
	}
}

void DrawSetDisplayWindow(OutputEnvironment& output_environment, std::vector<ColumnStatus>& column_statuses) {
	// text line showing # of entries in subset
	std::string subset_size_text = "Subset Size: " + std::to_string(output_environment.subset_entries.size());
	ImGui::Text(subset_size_text.c_str());


	// edit icon button
	ImGui::SameLine();
	std::string button_label = "Subset Table Options";
	ImTextureID button_tex = output_environment.GetTextureFromMap("edit");
	float line_height = ImGui::GetTextLineHeight();
	if (ImGui::ImageButton(button_label.c_str(), button_tex, ImVec2(line_height, line_height))) {
		ImGui::OpenPopup("table_options_popup");
	}
	if (ImGui::BeginPopup("table_options_popup")) {
		if (ImGui::BeginMenu("Column Toggling")) {
			for (ColumnStatus& col : column_statuses) {
				if (col.GetColumnInfo().togglable) {
					ImGui::Checkbox(col.GetColumnInfo().display_name.c_str(), &col.display_enabled);
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Column Coloring")) {
			for (ColumnStatus& col : column_statuses) {
				if (col.GetColumnInfo().colorable) {
					ImGui::Checkbox(col.GetColumnInfo().display_name.c_str(), &col.coloring_enabled);
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}

	std::vector<ColumnStatus> active_columns = {};
	for (ColumnStatus col : column_statuses) {
		if (col.IsEnabled()) {
			active_columns.push_back(col);
		}
	}
	int active_column_count = active_columns.size();
	ImGui::Text("Active Columns: %d", active_column_count);

	// pagination of table for performance reasons
	const ImU8 u8_one = 1;
	static bool inputs_step = true;
	static ImGuiInputTextFlags flags = ImGuiInputFlags_None;
	static ImU8 subset_page = 0;

	std::vector<std::string> page_size_labels = {"15", "30", "50", "100", "None"};
	std::vector<int> page_sizes = {15, 30, 50, 100, 10000};
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
		for (ColumnStatus active_column : active_columns) {
			ColumnInfo active_col_info = active_column.GetColumnInfo();
			std::string col_name = active_col_info.display_name;
			int col_flags = active_col_info.column_flags;
			int col_id = active_col_info.column_id;
			float col_width = active_col_info.column_width;
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
		int ending_index = std::min((int)output_environment.subset_entries.size(), starting_index + page_size);
		for (int subset_index = starting_index; subset_index < ending_index; subset_index++) {
			auto subset_entry = output_environment.subset_entries[subset_index];
			ImGui::TableNextRow();
			for (ColumnStatus active_column : active_columns) {
				ColumnInfo active_col_info = active_column.GetColumnInfo();
				ImGui::TableNextColumn();
				if (std::strcmp(ImGui::TableGetColumnName(), "Result #") == 0) {
					int displayed_index = subset_index + 1;
					ImGui::Text(std::to_string(displayed_index).c_str());
					continue;
				}
				if (subset_entry.HasConvertedData(active_col_info.query_name)) {
					ParameterValue param_val = subset_entry.GetParameterValue(active_col_info.query_name);
					if (active_column.IsColored()) {
						DisplayColor value_color = param_val.GetValueDisplayColor();
						ImVec4 cell_color = value_color.EvaluateColorWithIntensity(output_environment.table_color_intensity);
						ImU32 cell_bg_color = ImGui::GetColorU32(cell_color);
						ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
					}
					ImGui::Text(subset_entry.GetConvertedDataName(active_col_info.query_name).c_str());
				}
				else {
					ImGui::Text(subset_entry.GetRawData(active_col_info.query_name).c_str());
					std::cout << "NO CONVERTED DATA FOR " << active_col_info.query_name << std::endl;
				}
			}
		}
		ImGui::EndTable();
	}

	// display current page info
	int shown_page_index = subset_page + 1;
	int shown_page_count = page_count + 1;
	std::string curr_page_text = std::vformat("Page {0} of {1}", std::make_format_args(shown_page_index, shown_page_count));
	ImGui::Text(curr_page_text.c_str());
}

} // namespace monster_calculator