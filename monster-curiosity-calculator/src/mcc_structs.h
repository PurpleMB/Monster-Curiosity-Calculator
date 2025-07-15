#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "imgui.h"

namespace monster_calculator {

enum ParameterCategory {
	Enumerated,
	Numerical,
	Undefined
};

// TODO: use this to define display and possible values of different metrics we can refine query by
struct ParameterType {
	std::string display_name;
	std::string query_format;
	ParameterCategory catergory;
	std::vector<std::pair<std::string, std::string>> values;

	ParameterType(std::string name, std::string q_name, ParameterCategory cat, std::vector<std::pair<std::string, std::string>> vals) {
		display_name = name;
		query_format = q_name;
		catergory = cat;
		values = vals;
	}

	virtual ~ParameterType() = default;

	virtual ParameterCategory GetParameterCategory() {
		return catergory;
	}
};

struct BetterQueryParameter {
	std::string query_format;
	std::string query_value;
};

struct WindowParameters {
	std::string name;
	ImVec2 window_size;
	ImVec2 window_position;
	int imgui_window_settings;
	float internal_margin;
};

struct LogEntry {
	std::string timestamp;
	std::string message_code;
	std::string log_message;
};

struct ParameterSet {
	std::vector<std::vector<BetterQueryParameter>> subset_parameters;
	int parameter_count;

	ParameterSet() {
		subset_parameters = {{}};
		parameter_count = 0;
	}

	void AddParameter(const BetterQueryParameter& parameter, int parameter_group = 0) {
		if (parameter_group >= subset_parameters.size()) {
			subset_parameters.push_back({});
			parameter_group = subset_parameters.size() - 1;
		}

		subset_parameters[parameter_group].push_back(parameter);
		parameter_count++;
	}

	void RemoveParameter(const int target_group, const int group_index) {
		if (target_group >= subset_parameters.size()) {
			return;
		}
		if (group_index >= subset_parameters[group_index].size()) {
			return;
		}

		std::vector<BetterQueryParameter>& param_group = subset_parameters[target_group];
		param_group.erase(param_group.begin() + group_index);
		parameter_count--;
	}

	void ClearAllParameters() {
		subset_parameters.clear();
		parameter_count = 0;
	}
};

struct OutputEnvironment {
	std::vector<LogEntry> log_entries;
	std::vector<std::unordered_map<std::string, std::string>> subset_entries;
	ParameterSet subset_parameters;
	//std::vector<BetterQueryParameter> sorting_parameters;

	OutputEnvironment() {
		log_entries = {};
		subset_entries = {};
		subset_parameters = ParameterSet();
	}
};

struct SubsetColumnInfo {
	std::string display_name;
	std::string query_name;
	bool enabled;
	bool togglable;
};

} // namespace monster_calculator
 