#pragma once
#include <string>	// for string
#include <vector>	// for vector
#include <unordered_map> // used by converters
#include <unordered_set> // used by parameter groups
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

	DisplayColor GetValueDisplayColor() const {
		return value_color;
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

	bool operator==(const ParameterOperation& other) const {
		bool display_equal = display_name == other.display_name;
		bool db_equal = database_name == other.database_name;
		return display_equal && db_equal;
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

	DisplayColor GetParamDisplayColor() const {
		return parameter_color;
	}
};

// This enum is used to determine which method of displaying options works
// best for an EnumeratedParameterType.
enum PreferredEnumDisplay {
	Slider,
	ButtonGrid,
	Image,
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
			flat_value += (int)std::tolower(c);
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
	ParameterTypeConverter() {
		column_type_map = {};
	}

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

// This struct is meant to contain a set of parameters to be
// evaluated as a single logical clause where each parameter is connected
// by  logical AND.
struct ParameterGroup {
private:
	std::string group_name;
	DisplayColor group_color;
	std::vector<QueryParameter> parameters;
	std::unordered_set<std::string> accepted_entries;

public:
	ParameterGroup() {
		group_name = "Unnamed";
		group_color = kFuschiaColor;
		parameters = {};
		accepted_entries = {};
	}

	ParameterGroup(std::string name, DisplayColor color) {
		group_name = name;
		group_color = color;
		parameters = {};
		accepted_entries = {};
	}

	void AddParameter(const QueryParameter parameter) {
		parameters.push_back(parameter);
	}

	void RemoveParameter(const int param_index) {
		if (param_index >= parameters.size()) {
			return;
		}

		parameters.erase(parameters.begin() + param_index);
	}

	QueryParameter GetParameter(const int param_index) {
		if (param_index >= parameters.size()) {
			return QueryParameter();
		}

		return parameters[param_index];
	}
	
	void ClearParameters() {
		parameters.clear();
	}

	int GetParameterCount() const {
		return parameters.size();
	}

	std::string GetGroupName() const {
		return group_name;
	}

	DisplayColor GetGroupDisplayColor() const {
		return group_color;
	}

	std::unordered_set<std::string> GetAcceptedEntries() {
		return accepted_entries;
	}

	bool AcceptsEntry(std::string entry_id) {
		return accepted_entries.contains(entry_id);
	}

	void ClearAcceptedEntries() {
		accepted_entries.clear();
	}
	
	void AddAcceptedEntry(std::string entry) {
		accepted_entries.insert(entry);
	}

	std::string GenerateGroupQuery() const {
		std::string group_query = "(";

		for (int parameter_index = 0; parameter_index < parameters.size(); parameter_index++) {
			QueryParameter param = parameters[parameter_index];
			std::string query_statement = param.GetQuery();
			group_query += "(" + query_statement + ")";

			if (parameter_index < parameters.size() - 1) {
				group_query += " AND ";
			}
		}

		group_query += ")";
		return group_query;
	}
};

// This struct is meant to contain multiple ParameterGroups.
// Each group is independently evaluated and internally connected with ANDS, while
// groups in the set are connected by a logical OR.
// This allows the user to define sets looking for drastically different types
// of monsters.
struct ParameterSet {
private:
	std::vector<ParameterGroup> parameter_groups;
	bool resizable;

public:
	ParameterSet() {
		parameter_groups = {
			ParameterGroup("A", kRedColor)
		};
		resizable = false;
	}

	ParameterSet(int num_groups, bool allow_resize) {
		parameter_groups = {};
		for (int i = 0; i < num_groups; i++) {
			std::string name = std::to_string('A' + i);
			DisplayColor color = kWhiteColor;
			ParameterGroup group = ParameterGroup(name, color);
			parameter_groups.push_back(group);
		}
		resizable = allow_resize;
	}

	ParameterSet(std::vector<ParameterGroup> groups, bool allow_resize) {
		parameter_groups = {};
		for (int i = 0; i < groups.size(); i++) {
			parameter_groups.push_back(groups[i]);
		}
		resizable = allow_resize;
	}

	int GetGroupCount() {
		return parameter_groups.size();
	}

	ParameterGroup& GetParameterGroup(int group_index) {
		if (group_index >= parameter_groups.size()) {
			group_index = parameter_groups.size() - 1;
		}

		return parameter_groups[group_index];
	}

	const std::vector<ParameterGroup> GetGroupList() {
		return parameter_groups;
	}

	void AddParameter(const QueryParameter parameter, int parameter_group = 0) {
		if (parameter_group >= parameter_groups.size()) {
			if (!resizable) {
				return;
			}

			parameter_group = parameter_groups.size();
			std::string name = std::to_string('A' + parameter_group);
			DisplayColor color = kWhiteColor;
			ParameterGroup group = ParameterGroup(name, color);
			parameter_groups.push_back(group);
		}

		parameter_groups[parameter_group].AddParameter(parameter);
	}

	void RemoveParameter(const int target_group, const int param_index) {
		if (target_group >= parameter_groups.size()) {
			return;
		}

		parameter_groups[target_group].RemoveParameter(param_index);
	}

	void ClearAllParameters() {
		for (ParameterGroup& group : parameter_groups) {
			group.ClearParameters();
		}
	}

	std::string CombineGroupSets(std::string col_name) {
		bool empty_parameter_set = true;
		std::unordered_set<std::string> combined_set = {};
	
		for (ParameterGroup group : parameter_groups) {
			empty_parameter_set &= group.GetParameterCount() == 0;
			std::unordered_set<std::string> group_set = group.GetAcceptedEntries();
			std::cout << group_set.size() << std::endl;
			for (std::string entry : group_set) {
				combined_set.insert(entry);
			}
		}
		std::cout << combined_set.size() << std::endl;

		// I've elected to treat a totally empty parameter set as one that accepts all main table entries
		if (empty_parameter_set) {
			return col_name;
		}

		std::string set_list = "";
		int added_entries = 0;
		for (std::string entry : combined_set) {
			if (added_entries > 0) {
				set_list += ", ";
			}

			set_list += entry;
			added_entries++;
		}
		return set_list;
	}
};

} // namespace monster_calculator