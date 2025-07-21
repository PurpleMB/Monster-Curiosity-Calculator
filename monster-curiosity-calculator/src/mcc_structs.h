#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "imgui.h"

namespace monster_calculator {

enum ParameterCategory {
	Enumerated,
	Numerical,
	Undefined
};

enum SubsetColumnsIds {
	NameColumnId,
	DexColumnId,
	ColorColumnId,
	ShapeColumnId,
	HeightColumnId,
	WeightColumnId,
	PrimaryTypeColumnId,
	SecondaryTypeColumnId
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

	void AddParameter(const BetterQueryParameter parameter, int parameter_group = 0) {
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
		if (group_index >= subset_parameters[target_group].size()) {
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

struct SubsetEntry {
	std::unordered_map<std::string, std::string> entry_data;

	void AddData(std::string label, std::string value) {
		entry_data[label] = value;
	}

	std::string GetData(std::string label) {
		if (entry_data.contains(label)) {
			return entry_data[label];
		}
		return "No data found";
	}
};

struct SubsetComparator {
	ImGuiTableSortSpecs* sort_specs;

	SubsetComparator(ImGuiTableSortSpecs* specs) {
		sort_specs = specs;
	}

	bool operator()(SubsetEntry& lhs, SubsetEntry& rhs) {
		for (int i = 0; i < sort_specs->SpecsCount; i++) {
			const ImGuiTableColumnSortSpecs* sort_spec = &sort_specs->Specs[i];
			double delta = 0;
			switch (sort_spec->ColumnUserID) {
				case NameColumnId:
					delta = lhs.GetData("pretty_name").compare(rhs.GetData("pretty_name"));
					break;
				case DexColumnId:
					delta = std::stoi(lhs.GetData("dex_number")) - std::stoi(rhs.GetData("dex_number"));
					break;
				case ColorColumnId:
					delta = lhs.GetData("color").compare(rhs.GetData("color"));
					break;
				case ShapeColumnId:
					delta = lhs.GetData("shape").compare(rhs.GetData("shape"));
					break;
				case HeightColumnId:
					delta = std::stof(lhs.GetData("height")) - std::stof(rhs.GetData("height"));
					break;
				case WeightColumnId:
					delta = std::stod(lhs.GetData("weight")) - std::stod(rhs.GetData("weight"));
					break;
				case PrimaryTypeColumnId:
					delta = lhs.GetData("primary_type").compare(rhs.GetData("primary_type"));
					break;
				case SecondaryTypeColumnId:
					delta = lhs.GetData("secondary_type").compare(rhs.GetData("secondary_type"));
					break;
				default:
					std::cout << "ERROR: Attempting to sort unrecognized column" << std::endl;
					break;
			}
			if (delta > 0) {
				return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? 1 : 0;
			}
			else if (delta < 0) {
				return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? 0 : 1;
			}
		}
		return (std::stoi(lhs.GetData("id")) - std::stoi(rhs.GetData("id"))) < 0;
	}
};

struct OutputEnvironment {
	std::vector<LogEntry> log_entries;
	std::vector<SubsetEntry> subset_entries;
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
	int column_id;
};

} // namespace monster_calculator
 