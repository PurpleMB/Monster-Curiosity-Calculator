#pragma once
#include <string>
#include <vector>
#include <chrono>

#include <sqlite3.h>

#include "mcc_parameter_structs.h"
#include "mcc_value_structs.h"
#include "mcc_subset_structs.h"

namespace monster_calculator {

struct LogEntry {
	std::string timestamp;
	std::string message_code;
	std::string log_message;
};

struct OutputEnvironment {
	std::vector<LogEntry> log_entries;
	std::vector<SubsetEntry> subset_entries;
	ParameterSet subset_parameters;
	std::vector<ValueQuery> value_queries;

	// EXPERIMENTAL
	sqlite3* database_connection;

	OutputEnvironment() {
		log_entries = {};
		subset_entries = {};
		subset_parameters = ParameterSet();
		value_queries = {};

		database_connection = nullptr;
	}

	void ClearSubsetEntries() {
		subset_entries.clear();
	}

	void ConvertSubsetEntries(ParameterTypeConverter converter) {
		for (SubsetEntry& entry : subset_entries) {
			for (auto subset_map_iter = entry.raw_entry_data.begin(); subset_map_iter != entry.raw_entry_data.end(); subset_map_iter++) {
				std::string col_name = subset_map_iter->first;
				std::string col_val = subset_map_iter->second;
				if (converter.ContainsNameType(col_name)) {
					ParameterType* param_type_ptr = converter.GetParamTypeByName(col_name);
					ParameterCategory param_cat = converter.GetParamCategoryByName(col_name);
					if (param_cat == Enumerated || param_cat == EnumeratedSlider) {
						EnumeratedParameterType param_type = *dynamic_cast<EnumeratedParameterType*>(param_type_ptr);
						ParameterValue param_value = param_type.RetrieveParamValFromRawName(col_val);
						entry.AddConvertedData(col_name, param_value);
					}
					else {
						ParameterValue constructed_param_val = ParameterValue(col_val);
						param_type_ptr->SetValueColorForType(constructed_param_val);
						entry.AddConvertedData(col_name, constructed_param_val);
					}
				}
			}
		}
	}

	void LogError(const int event_code, const char* event_msg) {
		namespace ch = std::chrono;
		auto curr_time = ch::floor<ch::seconds>(ch::system_clock::now());

		std::string timestamp_text = std::format("{:%T}", curr_time);
		std::string error_code_text = std::to_string(event_code);
		std::string error_message_text = event_msg;

		LogEntry error_entry = {timestamp_text, error_code_text, error_message_text};
		log_entries.push_back(error_entry);
	}

	void LogSuccess(const char* event_msg) {
		LogError(0, event_msg);
	}

	std::string GenerateValueSetString(std::string table_name) {
		std::string set_text = "";
		for (int i = 0; i < value_queries.size(); i++) {
			ValueQuery query = value_queries[i];
			set_text += "\n" + query.GenerateQueryStatement(table_name);
			if (i < value_queries.size() - 1) {
				set_text += ",";
			}
		}
		return set_text;
	}
};

} // namespace monster_calculator