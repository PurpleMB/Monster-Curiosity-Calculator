#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>

#include <stdio.h>

#include <d3d11.h>

#include <sqlite3.h>

#include "mcc_parameter_structs.h"
#include "mcc_value_structs.h"
#include "mcc_subset_structs.h"

namespace monster_calculator {

enum EntryType {
	Neutral,
	Success,
	Warning,
	Error
};

struct LogEntry {
private:
	EntryType entry_type;
	std::string timestamp;
	std::string message_code;
	std::string log_message;

	std::string GenerateTimestamp() {
		namespace ch = std::chrono;
		auto curr_time = ch::floor<ch::seconds>(ch::system_clock::now());

		std::string timestamp_text = std::format("{:%T}", curr_time);
		return timestamp_text;
	}

public:
	LogEntry() {
		entry_type = Neutral;
		timestamp = GenerateTimestamp();
		message_code = "-1";
		log_message = "UNINITIALIZED LOG ENTRY";
	}

	LogEntry(EntryType type, std::string code, std::string messsage) {
		entry_type = type;
		timestamp = GenerateTimestamp();
		message_code = code;
		log_message = messsage;
	}

	EntryType GetEntryType() {
		return entry_type;
	}

	std::string GetEntryTimestamp() {
		return timestamp;
	}

	std::string GetEntryCode() {
		return message_code;
	}

	std::string GetEntryMessage() {
		return log_message;
	}
};

struct OutputEnvironment {
	std::vector<LogEntry> log_entries;
	std::vector<SubsetEntry> subset_entries;
	ParameterSet parameter_set;
	std::vector<ValueQuery> value_queries;

	// EXPERIMENTAL
	sqlite3* database_connection;
	std::unordered_map <std::string, ID3D11ShaderResourceView*> texture_map;
	bool show_settings;
	bool show_database_rebuild;
	bool show_program_log;
	bool show_user_guide;
	bool show_program_info;
	float table_color_intensity;
	ParameterTypeConverter converter;


	OutputEnvironment() {
		log_entries = {};
		subset_entries = {};
		parameter_set = ParameterSet();
		value_queries = {};

		database_connection = nullptr;
		texture_map = {};

		show_settings = false;
		show_database_rebuild = false;
		show_program_log = false;
		show_user_guide = false;
		show_program_info = false;

		table_color_intensity = .5f;

		converter = ParameterTypeConverter();
	}

	void SetTypeConverter(ParameterTypeConverter& passed_converter) {
		converter = passed_converter;
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
		std::string error_code_text = std::to_string(event_code);
		std::string error_message_text = event_msg;

		LogEntry error_entry = LogEntry(Error, error_code_text, error_message_text);
		log_entries.push_back(error_entry);
	}

	void LogWraning(const char* event_msg) {
		std::string warning_message_text = event_msg;

		LogEntry warning_entry = LogEntry(Warning, "0", warning_message_text);
		log_entries.push_back(warning_entry);
	}

	void LogNeutral(const char* event_msg) {
		std::string neutral_message_text = event_msg;

		LogEntry neutral_entry = LogEntry(Neutral, "0", neutral_message_text);
		log_entries.push_back(neutral_entry);
	}

	void LogSuccess(const char* event_msg) {
		std::string success_message_text = event_msg;

		LogEntry success_entry = LogEntry(Success,"0", success_message_text);
		log_entries.push_back(success_entry);
	}

	std::vector<int> GetUnlockedValueQueryIndices() {
		std::vector<int> active_query_indices = {};

		for (int i = 0; i < value_queries.size(); i++) {
			ValueQuery query = value_queries[i];
			if (query.IsLocked()) {
				continue;
			}
			active_query_indices.push_back(i);
		}

		return active_query_indices;
	}

	std::string GenerateValueQuerySetText(std::vector<int> unlocked_query_indices, std::string table_name) {
		std::string set_text = "";
		int added_queries = 0;
		for (int unlocked_index : unlocked_query_indices) {
			if (added_queries > 0) {
				set_text += ",";
			}

			ValueQuery query = value_queries[unlocked_index];
			set_text += "\n" + query.GenerateQueryStatement(table_name);
			added_queries += 1;
		}
		return set_text;
	}

	void StoreValueQueryResult(int value_query_index, std::string query_result) {
		if (value_query_index < 0 || value_query_index >= value_queries.size()) {
			return;
		}

		ValueQuery& query = value_queries[value_query_index];
		query.SetRawResultValue(query_result);

		std::string query_column = query.GetAssociatedColumnName();
		if (converter.ContainsNameType(query_column)) {
			ParameterType* param_type_ptr = converter.GetParamTypeByName(query_column);
			ParameterCategory param_cat = converter.GetParamCategoryByName(query_column);
			if (param_cat == Enumerated || param_cat == EnumeratedSlider) {
				EnumeratedParameterType param_type = *dynamic_cast<EnumeratedParameterType*>(param_type_ptr);
				ParameterValue param_value = param_type.RetrieveParamValFromRawName(query_result);
				query.UpdateResultDisplayInfo(param_value.display_name, param_value.value_color);
			}
			else {
				ParameterValue constructed_param_val = ParameterValue(query_result);
				param_type_ptr->SetValueColorForType(constructed_param_val);
				query.UpdateResultDisplayInfo(constructed_param_val.display_name, constructed_param_val.value_color);
			}
		}
	}

	void ConvertValueQueryResults(ParameterTypeConverter converter) {
		for (ValueQuery& query : value_queries) {
			std::string col_name = query.GetAssociatedColumnName();
			std::string col_val = query.GetRawResultValue();
			if (converter.ContainsNameType(col_name)) {
				ParameterType* param_type_ptr = converter.GetParamTypeByName(col_name);
				ParameterCategory param_cat = converter.GetParamCategoryByName(col_name);
				if (param_cat == Enumerated || param_cat == EnumeratedSlider) {
					EnumeratedParameterType param_type = *dynamic_cast<EnumeratedParameterType*>(param_type_ptr);
					ParameterValue param_value = param_type.RetrieveParamValFromRawName(col_val);
					query.UpdateResultDisplayInfo(param_value.display_name, param_value.value_color);
				}
				else {
					ParameterValue constructed_param_val = ParameterValue(col_val);
					param_type_ptr->SetValueColorForType(constructed_param_val);
					query.UpdateResultDisplayInfo(constructed_param_val.display_name, constructed_param_val.value_color);
				}
			}
		}
	}

	void AddTextureToMap(std::string key, ID3D11ShaderResourceView* texture) {
		texture_map[key] = texture;
	}

	ImTextureID GetTextureFromMap(std::string texture_key) {
		if (texture_map.contains(texture_key)) {
			ID3D11ShaderResourceView* texture = texture_map[texture_key];
			return (ImTextureID)(intptr_t)texture;
		}
		return (ImTextureID)(intptr_t)nullptr;
	}
};

} // namespace monster_calculator