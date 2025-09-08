#pragma once
#include <string>	// for string
#include <vector>	// for vector
#include <unordered_map> // used by converters
#include <memory>	//	shared_ptr in converters

#include <iostream>

#include "mcc_display_structs.h"
#include "mcc_display_constants.h"

namespace monster_calculator {

// This struct encapsulates the data for a single possible value of a ParameterType.
// For example, a parameter value for a monster typing may have values like "normal", "Normal"
// and an ImVec4 that looks white when interpreted as a color.
struct ParameterValue {
	std::string display_name;
	std::string database_name;
	DisplayColor value_color;
	int sorting_value; // really only used for enum parameter values to allow custom sorting order

	ParameterValue() {
		display_name = "UNINITIALIZED PARAMETER VALUE DISPLAY NAME";
		database_name = "UNINITIALIZED PARAMETER VALUE DATABASE NAME";
		value_color = kRedColor;
		sorting_value = -1;
	}

	ParameterValue(std::string value_name) {
		display_name = value_name;
		database_name = value_name;
		value_color = kRedColor;
		sorting_value = -1;
	}

	ParameterValue(std::string dis_name, std::string db_name, DisplayColor color) {
		display_name = dis_name;
		database_name = db_name;
		value_color = color;
		sorting_value = -1;
	}

	ParameterValue(std::string dis_name, std::string db_name, DisplayColor color, int sort_val) {
		display_name = dis_name;
		database_name = db_name;
		value_color = color;
		sorting_value = sort_val;
	}

	ImVec4 GetParameterColor() const {
		return value_color.GetColorValues();
	}

	int GetSortValue() const {
		return sorting_value;
	}
};

struct ParameterOperation : ParameterValue {
	std::vector<std::string> operands;

	ParameterOperation(std::string dis_name, std::string db_name, DisplayColor color, std::vector<std::string> ops) :
		ParameterValue(dis_name, db_name, color) {
		operands = ops;
	}
};

// This enum defines the possible types of parameters the user may set.
// Undefined is only used for improperly defined ParameterTypes,
// while Enumerated represents things like Type, Region, etc. while
// Numerical is used for values such as Health, Speed, etc.
enum ParameterCategory {
	Enumerated,
	EnumeratedSlider,
	Open,
	Integer,
	Decimal,
	Undefined
};

// This struct defines the general structure of an entire type of value that may be parameterized
// (Health, Dex #, etc.) and contains info about how the database wants to see that parameter,
// how to show the user that parameter, and information regarding all possible values for the type.
struct ParameterType {
	std::string display_name;
	std::string database_format;
	std::string display_format;
	DisplayColor parameter_color;
	std::vector<ParameterOperation> operations;

	ParameterType() {
		display_name = "UNINITIALIZED DISPLAY NAME";
		database_format = "UNINITIALIZED DATABASE FORMAT";
		display_format = "UNINITIALIZED DISPLAY FORMAT";
		parameter_color = kWhiteColor;
		operations = {};
	}

	ParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color, std::vector<ParameterOperation> ops) {
		display_name = dis_name;
		display_format = dis_format;
		database_format = db_format;
		parameter_color = color;
		operations = ops;
	}

	virtual ~ParameterType() = default;

	virtual ParameterCategory GetParameterCategory() const {
		return Undefined;
	}

	virtual void SetValueColorForType(ParameterValue& value) const {
		value.value_color = kFuschiaColor;
	}

	ImVec4 GetParameterColor() const {
		return parameter_color.GetColorValues();
	}
};

// This enum is used to determine which method of displaying options works
// best for an EnumeratedParameterType.
enum PreferredEnumDisplay {
	Slider,
	ButtonGrid,
	Dropdown
};

struct EnumeratedParameterType : ParameterType {
	std::vector<ParameterValue> values;
	std::unordered_map<std::string, ParameterValue> db_name_val_map;
	PreferredEnumDisplay display_method;

	// only for use by ButtonGrid
	ImVec2 button_size;
	int buttons_per_row;

	EnumeratedParameterType() : ParameterType() {
		values = {};
		db_name_val_map = {};
		display_method = Dropdown;
		button_size = ImVec2(0.0f, 0.0f);
		buttons_per_row = 1;
	}

	EnumeratedParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color, std::vector<ParameterOperation> ops, std::vector<ParameterValue> vals, PreferredEnumDisplay display) :
		ParameterType(dis_name, dis_format, db_format, color, ops) {
		values = vals;
		db_name_val_map = {};
		for (ParameterValue param_val : vals) {
			db_name_val_map[param_val.database_name] = param_val;
		}
		display_method = display;
		button_size = ImVec2(0.0f, 0.0f);
		buttons_per_row = 1;
	}

	EnumeratedParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color, std::vector<ParameterOperation> ops, std::vector<ParameterValue> vals, PreferredEnumDisplay display,
		ImVec2 btn_size, int btn_per_row) :
		ParameterType(dis_name, dis_format, db_format, color, ops) {
		values = vals;
		db_name_val_map = {};
		for (ParameterValue param_val : vals) {
			db_name_val_map[param_val.database_name] = param_val;
		}
		display_method = display;
		button_size = btn_size;
		buttons_per_row = btn_per_row;
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Enumerated;
	}

	PreferredEnumDisplay GetPreferredDisplay() const {
		return display_method;
	}

	ImVec2 GetButtonSize() const {
		return button_size;
	}

	int GetButtonsPerRow() const {
		return buttons_per_row;
	}

	ParameterValue RetrieveParamValFromRawName(std::string raw_name) {
		if (db_name_val_map.contains(raw_name)) {
			return db_name_val_map[raw_name];
		}
		return ParameterValue();
	}
};

struct OpenParameterType : ParameterType {
	// this vector should contain at least 2 colors for color interpolation in numerical parameters
	std::vector<DisplayColor> possible_value_colors;

	OpenParameterType() : ParameterType() {
		possible_value_colors = {
			kRedColor, kFuschiaColor
		};
	}

	OpenParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color, std::vector<ParameterOperation> ops, std::vector<DisplayColor> colors) :
		ParameterType(dis_name, dis_format, db_format, color, ops) {
		possible_value_colors = colors;
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Open;
	}

	virtual void SetValueColorForType(ParameterValue& value) const {
		// generate int sum of characters to index into colors list
		int flat_value = 0;
		for (char c : value.display_name) {
			flat_value += (int)c;
		}
		value.value_color = possible_value_colors[flat_value % possible_value_colors.size()];
	}
};

struct IntegerParameterType : OpenParameterType {
	int min_value;
	int max_value;

	// this vector should be of size <= (possible_value_colors.size() - 1) to avoid OoB errors
	std::vector<float> value_color_thresholds;

	IntegerParameterType() : OpenParameterType() {
		min_value = -1;
		max_value = -1;
		value_color_thresholds = {0.0f};
	}

	IntegerParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color,
		std::vector<ParameterOperation> ops, std::vector<DisplayColor> colors, int min, int max, std::vector<float> color_thresholds) :
		OpenParameterType(dis_name, dis_format, db_format, color, ops, colors) {
		min_value = min;
		max_value = max;
		if (color_thresholds.size() >= possible_value_colors.size()) {
			auto threshold_start = color_thresholds.begin();
			int threshold_size = possible_value_colors.size() > 2 ? possible_value_colors.size() -1 : 1;
			auto threshold_end = threshold_start + threshold_size;
			value_color_thresholds = std::vector(threshold_start, threshold_end);
		} else {
			value_color_thresholds = color_thresholds;
		}
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Integer;
	}

	virtual void SetValueColorForType(ParameterValue& value) const {
		int converted_value = std::stoi(value.display_name);
		float value_range_percent = (converted_value - min_value) / (float)(max_value - min_value);
		int floor_color_index = -1;
		for (int i = 0; i < value_color_thresholds.size(); i++) {
			if (value_range_percent >= value_color_thresholds[i]) {
				floor_color_index = i;
			}
			else {
				break;
			}
		}
		float floor_threshold = value_color_thresholds[floor_color_index];
		float ceil_threshold = (floor_color_index < value_color_thresholds.size() - 1) ? value_color_thresholds[floor_color_index + 1] : 1.0f;
		DisplayColor floor_color = possible_value_colors[floor_color_index];
		DisplayColor ceil_color = possible_value_colors[floor_color_index + 1];
		float color_lerp_t = (value_range_percent - floor_threshold) / (ceil_threshold - floor_threshold);
		DisplayColor lerped_color = DisplayColor::InterpolateColors(floor_color, ceil_color, color_lerp_t);
		value.value_color = lerped_color;
	}
};

struct DecimalParameterType : OpenParameterType {
	double min_value;
	double max_value;

	// this vector should be of size <= (possible_value_colors.size() - 1) to avoid OoB errors
	std::vector<float> value_color_thresholds;

	DecimalParameterType() : OpenParameterType() {
		min_value = -1.0;
		max_value = -1.0;
		value_color_thresholds = {0.0f};
	}

	DecimalParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color,
		std::vector<ParameterOperation> ops, std::vector<DisplayColor> colors, double min, double max, std::vector<float> color_thresholds) :
		OpenParameterType(dis_name, dis_format, db_format, color, ops, colors) {
		min_value = min;
		max_value = max;
		if (color_thresholds.size() >= possible_value_colors.size()) {
			auto threshold_start = color_thresholds.begin();
			int threshold_size = possible_value_colors.size() > 2 ? possible_value_colors.size() - 1 : 1;
			auto threshold_end = threshold_start + threshold_size;
			value_color_thresholds = std::vector(threshold_start, threshold_end);
		}
		else {
			value_color_thresholds = color_thresholds;
		}
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Decimal;
	}

	virtual void SetValueColorForType(ParameterValue& value) const {
		double converted_value = std::stod(value.display_name);
		float value_range_percent = (converted_value - min_value) / (float)(max_value - min_value);
		int floor_color_index = -1;
		for (int i = 0; i < value_color_thresholds.size(); i++) {
			if (value_range_percent >= value_color_thresholds[i]) {
				floor_color_index = i;
			}
			else {
				break;
			}
		}
		float floor_threshold = value_color_thresholds[floor_color_index];
		float ceil_threshold = (floor_color_index < value_color_thresholds.size() - 1) ? value_color_thresholds[floor_color_index + 1] : 1.0f;
		DisplayColor floor_color = possible_value_colors[floor_color_index];
		DisplayColor ceil_color = possible_value_colors[floor_color_index + 1];
		float color_lerp_t = (value_range_percent - floor_threshold) / (ceil_threshold - floor_threshold);
		DisplayColor lerped_color = DisplayColor::InterpolateColors(floor_color, ceil_color, color_lerp_t);
		value.value_color = lerped_color;
	}
};

struct ParameterTypeConverter {
private:
	std::unordered_map<std::string, std::shared_ptr<ParameterType>> column_type_map;
	std::unordered_map<int, std::string> column_id_name_map;

public:
	ParameterTypeConverter(std::unordered_map<std::string, std::shared_ptr<ParameterType>> column_type_mappings) {
		column_type_map = column_type_mappings;
	}

	bool ContainsNameType(std::string col_name) const {
		return column_type_map.contains(col_name);
	}

	ParameterType* GetParamTypeByName(std::string col_name) const {
		if (column_type_map.contains(col_name)) {
			ParameterType* param_type_ptr = column_type_map.at(col_name).get();
			return param_type_ptr;
		}
		return nullptr;
	}

	ParameterCategory GetParamCategoryByName(std::string col_name) const {
		if (column_type_map.contains(col_name)) {
			return column_type_map.at(col_name).get()->GetParameterCategory();
		}
		return Undefined;
	}
};

// This struct is meant to hold the sum of data needed to pass a query component 
// to the database as well as display that query in a pleasing way to the user.
// Thus, this struct contains a FormatStatement and DisplayStatement that ideally
// contain data representing the same query as seen by the DB and the user.
struct QueryParameter {
private:
	std::string query_string;
	TableCellDisplayInfo parameter_info;
	TableCellDisplayInfo operation_info;
	TableCellDisplayInfo value_info;

public:
	QueryParameter() {
		query_string = "UNINITIALIZED QUERY STRING";
		parameter_info = TableCellDisplayInfo();
		operation_info = TableCellDisplayInfo();
		value_info = TableCellDisplayInfo();
	}

	void SetQuery(std::string query) {
		query_string = query;
	}

	void SetParameterInfo(TableCellDisplayInfo param_info) {
		parameter_info = param_info;
	}

	void SetOperationInfo(TableCellDisplayInfo oper_info) {
		operation_info = oper_info;
	}

	void SetValueInfo(TableCellDisplayInfo val_info) {
		value_info = val_info;
	}

	std::string GetQuery() {
		return query_string;
	}

	TableCellDisplayInfo GetParameterDisplayInfo() {
		return parameter_info;
	}

	TableCellDisplayInfo GetOperationDisplayInfo() {
		return operation_info;
	}

	TableCellDisplayInfo GetValueDisplayInfo() {
		return value_info;
	}
};

// This struct is meant to contain multiple sets of QueryParameters.
// Each set may contain an arbitrary number of QueryParameters, with each set
// being evaluated to its own logical statement.
// This allows the user to define sets looking for drastically different types
// of monsters.
struct ParameterSet {
	int group_count;
	std::vector<std::vector<QueryParameter>> parameter_groups;
	std::vector<std::string> group_names;
	std::vector<DisplayColor> group_colors;
	int total_parameter_count;
	bool resizable;

	ParameterSet() {
		group_count = 1;
		parameter_groups = {{}};
		group_names = {"A"};
		group_colors = {kWhiteColor};
		total_parameter_count = 0;
		resizable = false;
	}

	ParameterSet(int groups, bool allow_resize) {
		group_count = groups;
		parameter_groups = {};
		group_names = {};
		for (int i = 0; i < group_count; i++) {
			parameter_groups.push_back({});
			group_names.push_back(std::to_string('A' + i));
		}
		group_colors = {kWhiteColor};
		total_parameter_count = 0;
		resizable = allow_resize;
	}

	ParameterSet(int groups, bool allow_resize, std::vector<std::string> names, std::vector<DisplayColor>& colors) {
		group_count = groups;
		parameter_groups = {};
		for (int i = 0; i < group_count; i++) {
			parameter_groups.push_back({});
		}
		group_names = names;
		group_colors = colors;
		total_parameter_count = 0;
		resizable = allow_resize;
	}

	int GetGroupCount() {
		return group_count;
	}

	void AddParameter(const QueryParameter parameter, int parameter_group = 0) {
		if (parameter_group >= parameter_groups.size()) {
			if (!resizable) {
				return;
			}
			parameter_groups.push_back({});
			group_count = parameter_groups.size();
			parameter_group = parameter_groups.size() - 1;
		}

		parameter_groups[parameter_group].push_back(parameter);
		total_parameter_count++;
	}

	void RemoveParameter(const int target_group, const int group_index) {
		if (target_group >= parameter_groups.size()) {
			return;
		}
		if (group_index >= parameter_groups[target_group].size()) {
			return;
		}

		std::vector<QueryParameter>& param_group = parameter_groups[target_group];
		param_group.erase(param_group.begin() + group_index);
		total_parameter_count--;
	}

	void ClearAllParameters() {
		for (std::vector<QueryParameter>& param_group : parameter_groups) {
			param_group.clear();
		}
		total_parameter_count = 0;
	}

	std::string GetGroupName(int group_index) const {
		int name_index = group_index % group_names.size();
		std::string group_name = group_names[name_index];
		return group_name;
	}

	std::vector<std::string> GetGroupNameList() const {
		return group_names;
	}

	ImVec4 GetGroupColor(int group_index) const {
		int color_index = group_index % group_colors.size();
		DisplayColor group_display_color = group_colors[color_index];
		return group_display_color.GetColorValues();
	}

	std::string GetGroupQueryString(int group_index) const {
		if (group_index < 0 || group_index >= parameter_groups.size()) {
			return "";
		}
		if (parameter_groups[group_index].size() == 0) {
			return "";
		}

		std::vector<QueryParameter> parameter_group = parameter_groups[group_index];
		std::string group_query = "(";

		for (int parameter_index = 0; parameter_index < parameter_group.size(); parameter_index++) {
			QueryParameter param = parameter_group[parameter_index];
			std::string query_statement = param.GetQuery();
			group_query += "(" + query_statement + ")";

			if (parameter_index < parameter_group.size() - 1) {
				group_query += " AND ";
			}
		}

		group_query += ")";
		return group_query;
	}

	std::string GetSetQueryString() const {
		if (total_parameter_count == 0) {
			return "( true )";
		}

		std::string set_query = "";
		int active_groups = 0;

		for (int group_index = 0; group_index < parameter_groups.size(); group_index++) {
			if (parameter_groups[group_index].size() == 0) {
				continue;
			}

			active_groups++;
			if (active_groups > 1) {
				set_query += " OR ";
			}

			set_query += GetGroupQueryString(group_index);
		}

		return set_query;
	}
};

} // namespace monster_calculator