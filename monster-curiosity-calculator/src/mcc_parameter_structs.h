#pragma once
#include <string>	// for string
#include <vector>	// for vector
#include <format>	// for string formatting

#include "imgui.h"	// for access to ImGui color type

namespace monster_calculator {

// This struct is meant to hold a format string and some amount of argument strings
// These strings can then be evaluated to form a single dynamic query statement for use
// with the SQL database
// ex: "health = {0}" with an argument of "10" convets to "health = 10"
struct FormatStatement {
	std::string format;
	std::string argument;

	FormatStatement() {
		format = "";
		argument = "";
	}

	FormatStatement(std::string form, std::string arg) {
		format = form;
		argument = arg;
	}

	std::string EvaluateStatement() {
		std::string evaluated_statement = std::vformat(format, std::make_format_args(argument));
		return evaluated_statement;
	}
};

// This struct is a child of FormatStatement meant to add additional data for 
// displaying the statement inside a user-facing table. This includes such things as
// desired table cell colors for the statement of arguments
struct DisplayStatement : FormatStatement {
	ImVec4 format_color;
	ImVec4 argument_color;

	DisplayStatement() : FormatStatement() {
		format_color = ImVec4(0, 0, 0, 0);
		argument_color = ImVec4(0, 0, 0, 0);
	}

	DisplayStatement(std::string form, std::string arg, ImVec4 format_col, ImVec4 arg_col) : FormatStatement(form, arg) 
	{
		format_color = format_col;
		argument_color = arg_col;
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
		this->database_statement = db_statement;
		this->display_statement = dis_statement;
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
	int total_parameter_count;
	bool resizable;

	ParameterSet() {
		group_count = 1;
		parameter_groups = {{}};
		total_parameter_count = 0;
		resizable = false;
	}

	ParameterSet(int groups, bool allow_resize) {
		group_count = groups;
		parameter_groups = {};
		for (int i = 0; i < group_count; i++) {
			parameter_groups.push_back({});
		}
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
		std::cout << total_parameter_count;
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
};

} // namespace monster_calculator