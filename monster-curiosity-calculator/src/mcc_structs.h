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

struct OutputEnvironment {
	std::vector<LogEntry> log_entries;
	std::vector<std::unordered_map<std::string, std::string>> subset_entries;
	std::vector<BetterQueryParameter> subset_parameters;
	std::vector<BetterQueryParameter> sorting_parameters;
};

/*
struct EntryInfo {
	int unique_id;
	std::string name;
	int dex_num;
	std::string generation;
	bool form_switchable;
	std::string color;
	std::string shape;
	std::string growth_rate;
	int base_exp;
	int base_happiness;
	int catch_rate;
	int hatch_counter;
	int 
		"gender_rate INT NOT NULL,"
		"dimorphic INT NOT NULL, "
		"primary_egg_group TEXT NOT NULL,"
		"secondary_egg_group TEXT NOT NULL,"
		"is_default INT NOT NULL,"
		"is_baby INT NOT NULL,"
		"is_legendary INT NOT NULL,"
		"is_mythical INT NOT NULL,"
		"height DOUBLE NOT NULL,"
		"weight DOUBLE NOT NULL,"
		"primary_type TEXT NOT NULL,"
		"secondary_type TEXT NOT NULL,"
		"ability_1 TEXT NOT NULL,"
		"ability_2 TEXT NOT NULL,"
		"hidden_ability TEXT NOT NULL,"
		"hp INTEGER NOT NULL,"
		"attack INTEGER NOT NULL,"
		"defense INTEGER NOT NULL,"
		"special_attack INTEGER NOT NULL,"
		"special_defense INTEGER NOT NULL,"
		"speed INTEGER NOT NULL,"
		"stat_total INTEGER NOT NULL"
		");"
};
*/

} // namespace monster_calculator
 