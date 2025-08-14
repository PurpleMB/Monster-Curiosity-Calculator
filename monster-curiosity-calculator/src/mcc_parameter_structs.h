#pragma once
#include <string>	// for string
#include <vector>	// for vector
#include <format>	// for string formatting

#include "imgui.h"	// for access to ImGui color type

#include "mcc_display_structs.h"
#include "mcc_display_constants.h"

namespace monster_calculator {

// This enum defines the possible types of parameters the user may set.
// Undefined is only used for improperly defined ParameterTypes,
// while Enumerated represents things like Type, Region, etc. while
// Numerical is used for values such as Health, Speed, etc.
enum ParameterCategory {
	Enumerated,
	Open,
	Numerical,
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

	ParameterType() {
		display_name = "UNINITIALIZED DISPLAY NAME";
		database_format = "UNINITIALIZED DATABASE FORMAT";
		display_format = "UNINITIALIZED DISPLAY FORMAT";
		parameter_color = kWhiteColor;
	}

	ParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color) {
		display_name = dis_name;
		display_format = dis_format;
		database_format = db_format;
		parameter_color = color;
	}

	virtual ~ParameterType() = default;

	virtual ParameterCategory GetParameterCategory() const {
		return Undefined;
	}

	ImVec4 GetParameterColor() const {
		return parameter_color.GetColorValues();
	}
};

// This struct encapsulates the data for a single possible value of a ParameterType.
// For example, a parameter value for a monster typing may have values like "normal", "Normal"
// and an ImVec4 that looks white when interpreted as a color.
struct ParameterValue {
	std::string display_name;
	std::string database_name;
	DisplayColor value_color;

	ParameterValue(std::string dis_name, std::string db_name, DisplayColor color) {
		display_name = dis_name;
		database_name = db_name;
		value_color = color;
	}

	ImVec4 GetParameterColor() const {
		return value_color.GetColorValues();
	}
};

struct EnumeratedParameterType : ParameterType {
	std::vector<ParameterValue> values;

	EnumeratedParameterType() : ParameterType() {
		values = {};
	}

	EnumeratedParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color, std::vector<ParameterValue> vals) :
		ParameterType(dis_name, dis_format, db_format, color) {
		values = vals;
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Enumerated;
	}
};

struct ParameterOperation : ParameterValue{
	std::vector<std::string> operands;

	ParameterOperation(std::string dis_name, std::string db_name, DisplayColor color, std::vector<std::string> ops) :
		ParameterValue(dis_name, db_name, color) {
		operands = operands;
	}
};

struct OpenParameterType : ParameterType {
	int data_type;
	std::vector<ParameterOperation> operations;

	OpenParameterType() : ParameterType() {
		data_type = ImGuiDataType_Bool;
		operations = {};
	}

	OpenParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color, 
		int type, std::vector<ParameterOperation> ops) :
		ParameterType(dis_name, dis_format, db_format, color) {
		data_type = type;
		operations = ops;
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Open;
	}
};

struct NumericalParameterType : OpenParameterType {
	int min_value;
	int max_value;

	NumericalParameterType() : OpenParameterType() {
		min_value = -1;
		max_value = -1;
	}

	NumericalParameterType(std::string dis_name, std::string dis_format, std::string db_format, DisplayColor color,
		int type, std::vector<ParameterOperation> ops, int min, int max) :
		OpenParameterType(dis_name, dis_format, db_format, color, type, ops) {
		min_value = min;
		max_value = max;
	}

	virtual ParameterCategory GetParameterCategory() const {
		return Numerical;
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

// This struct is meant to hold the sum of data needed to pass a query component 
// to the database as well as display that query in a pleasing way to the user.
// Thus, this struct contains a FormatStatement and DisplayStatement that ideally
// contain data representing the same query as seen by the DB and the user.
struct QueryParameter {
	FormatStatement database_statement;
	DisplayStatement display_statement;

	QueryParameter() {
		database_statement = FormatStatement();
		display_statement = DisplayStatement();
	}

	QueryParameter(FormatStatement db_statement, DisplayStatement dis_statement) {
		database_statement = db_statement;
		display_statement = dis_statement;
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