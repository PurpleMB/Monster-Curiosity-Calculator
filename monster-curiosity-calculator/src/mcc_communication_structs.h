#pragma once
#include <string>
#include <vector>

#include "mcc_parameter_structs.h"
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
	QueryParameter value_parameter;
	//std::vector<BetterQueryParameter> sorting_parameters;

	OutputEnvironment() {
		log_entries = {};
		subset_entries = {};
		subset_parameters = ParameterSet();
		value_parameter = QueryParameter();
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
};

} // namespace monster_calculator