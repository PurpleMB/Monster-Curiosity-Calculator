#pragma once
#include <string>	// for string
#include <vector>	// for vector
#include <format>	// for string formatting

#include "imgui.h"	// for access to ImGui color type

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

	ImVec4 GetParameterColor() const {
		return parameter_color.GetColorValues();
	}
};

struct EnumeratedParameterType : ParameterType {
	std::vector<ParameterValue> values;

	EnumeratedParameterType() : ParameterType() {
		values = {};
	}

	EnumeratedParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color, std::vector<ParameterOperation> ops, std::vector<ParameterValue> vals) :
		ParameterType(dis_name, dis_format, db_format, color, ops) {
		values = vals;
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Enumerated;
	}
};

struct SliderEnumeratedParameterType : EnumeratedParameterType {
	SliderEnumeratedParameterType() : EnumeratedParameterType() {

	}

	SliderEnumeratedParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color, std::vector<ParameterOperation> ops, std::vector<ParameterValue> vals) :
		EnumeratedParameterType(dis_name, dis_format, db_format, color, ops, vals) {

	}

	virtual ParameterCategory GetParameterCategory() const {
		return EnumeratedSlider;
	}
};

struct OpenParameterType : ParameterType {

	OpenParameterType() : ParameterType() {

	}

	OpenParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color, std::vector<ParameterOperation> ops) :
		ParameterType(dis_name, dis_format, db_format, color, ops) {

	}

	virtual ParameterCategory GetParameterCategory() const {
		return Open;
	}
};

struct IntegerParameterType : OpenParameterType {
	int min_value;
	int max_value;

	IntegerParameterType() : OpenParameterType() {
		min_value = -1;
		max_value = -1;
	}

	IntegerParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color,
		std::vector<ParameterOperation> ops, int min, int max) :
		OpenParameterType(dis_name, dis_format, db_format, color, ops) {
		min_value = min;
		max_value = max;
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Integer;
	}
};

struct DecimalParameterType : OpenParameterType {
	double min_value;
	double max_value;

	DecimalParameterType() : OpenParameterType() {
		min_value = -1.0;
		max_value = -1.0;
	}

	DecimalParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color,
		std::vector<ParameterOperation> ops, double min, double max) :
		OpenParameterType(dis_name, dis_format, db_format, color, ops) {
		min_value = min;
		max_value = max;
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Decimal;
	}
};

// This struct is meant to hold a format string and some amount of argument strings
// These strings can then be evaluated to form a single dynamic query statement for use
// with the SQL database
// ex: "health = {0}" with an argument of "10" converts to "health = 10"
struct FormatStatement {
	std::string format;
	std::string argument;

	FormatStatement() {
		format = "UNINITIALIZED FORMAT";
		argument = "UNINITIALIZED ARGUMENT NAME";
	}

	FormatStatement(std::string form, std::string arg) {
		format = form;
		argument = arg;
	}

	std::string EvaluateStatement() const {
		std::string evaluated_statement = std::vformat(format, std::make_format_args(argument));
		return evaluated_statement;
	}
};

// This struct is a child of FormatStatement meant to add additional data for 
// displaying the statement inside a user-facing table. This includes such things as
// desired table cell colors for the statement of arguments
struct DisplayStatement : FormatStatement {
	std::string parameter_name;
	DisplayColor parameter_color;
	DisplayColor argument_color;

	DisplayStatement() : FormatStatement() {
		parameter_name = "UNITIALIZED PARAMETER NAME";
		parameter_color = DisplayColor();
		argument_color = DisplayColor();
	}

	DisplayStatement(std::string form, std::string arg, std::string param_name, DisplayColor param_col, DisplayColor arg_col) : FormatStatement(form, arg) 
	{
		parameter_name = param_name;
		parameter_color = param_col;
		argument_color = arg_col;
	}

	std::string GetParameterName() {
		return parameter_name;
	}

	std::string GetArgumentName() {
		return argument;
	}

	ImVec4 GetParameterColor() {
		return parameter_color.GetColorValues();
	}

	ImVec4 GetArgumentColor() {
		return argument_color.GetColorValues();
	}
};

struct ColumnDisplayInfo {
private:
	std::string column_text;
	DisplayColor column_color;

public:
	ColumnDisplayInfo() {
		column_text = "UNINITIALIZED COLUMN TEXT";
		column_color = DisplayColor();
	}

	ColumnDisplayInfo(std::string text, DisplayColor color) {
		column_text = text;
		column_color = color;
	}

	std::string GetText() const {
		return column_text;
	}

	DisplayColor GetColor() const {
		return column_color;
	}
};

// This struct is meant to hold the sum of data needed to pass a query component 
// to the database as well as display that query in a pleasing way to the user.
// Thus, this struct contains a FormatStatement and DisplayStatement that ideally
// contain data representing the same query as seen by the DB and the user.
struct QueryParameter {
private:
	std::string query_string;
	ColumnDisplayInfo parameter_info;
	ColumnDisplayInfo operation_info;
	ColumnDisplayInfo value_info;

public:
	QueryParameter() {
		query_string = "UNINITIALIZED QUERY STRING";
		parameter_info = ColumnDisplayInfo();
		operation_info = ColumnDisplayInfo();
		value_info = ColumnDisplayInfo();
	}

	void SetQuery(std::string query) {
		query_string = query;
	}

	void SetParameterInfo(ColumnDisplayInfo param_info) {
		parameter_info = param_info;
	}

	void SetOperationInfo(ColumnDisplayInfo oper_info) {
		operation_info = oper_info;
	}

	void SetValueInfo(ColumnDisplayInfo val_info) {
		value_info = val_info;
	}

	std::string GetQuery() {
		return query_string;
	}

	ColumnDisplayInfo GetParameterDisplayInfo() {
		return parameter_info;
	}

	ColumnDisplayInfo GetOperationDisplayInfo() {
		return operation_info;
	}

	ColumnDisplayInfo GetValueDisplayInfo() {
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
	std::vector<DisplayColor> group_colors;
	int total_parameter_count;
	bool resizable;

	ParameterSet() {
		group_count = 1;
		parameter_groups = {{}};
		group_colors = {kWhiteColor};
		total_parameter_count = 0;
		resizable = false;
	}

	ParameterSet(int groups, bool allow_resize) {
		group_count = groups;
		parameter_groups = {};
		for (int i = 0; i < group_count; i++) {
			parameter_groups.push_back({});
		}
		group_colors = {kWhiteColor};
		total_parameter_count = 0;
		resizable = allow_resize;
	}

	ParameterSet(int groups, bool allow_resize, std::vector<DisplayColor>& colors) {
		group_count = groups;
		parameter_groups = {};
		for (int i = 0; i < group_count; i++) {
			parameter_groups.push_back({});
		}
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

	ImVec4 GetGroupColor(int group_index) const {
		int color_index = group_index % group_colors.size();
		DisplayColor group_display_color = group_colors[color_index];
		return group_display_color.GetColorValues();
	}
};

} // namespace monster_calculator