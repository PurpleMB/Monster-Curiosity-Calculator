#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

#include "imgui.h" // for acces to ImVec4 datatype

#include "mcc_parameter_structs.h"
#include "mcc_parameter_constants.h"

namespace monster_calculator {

struct DisplayColor {
private:
	std::string color_name;
	ImVec4 color_value;

public:
	DisplayColor() {
		color_name = "UNINITIALIZED COLOR";
		color_value = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	DisplayColor(std::string name, ImVec4 values) {
		color_name = name;
		color_value = values;
	}

	std::string GetColorName() const {
		return color_name;
	}

	ImVec4 GetColorValues() const {
		return color_value;
	}
};

enum SubsetColumnsIds {
	NumberColumnId,
	NameColumnId,
	DexColumnId,
	ColorColumnId,
	ShapeColumnId,
	HeightColumnId,
	WeightColumnId,
	PrimaryTypeColumnId,
	SecondaryTypeColumnId,
	GenerationColumnId,
	FormSwitchColumnId,
	GrowthRateColumnId,
	BaseExpColumnId,
	BaseHappyColumnId,
	CatchRateColumnId,
	DimorphicColumnId,
	PrimEggColumnId,
	SecEggColumnId,
	IsDefaultColumnId,
	IsBabyColumnId,
	IsLegendColumnId,
	IsMythColumnId,
	AbilOneColumnId,
	AbilTwoColumnId,
	AbilHiddenColumnId,
	HealthColumnId,
	AttackColumnId,
	DefenseColumnId,
	SpeAtkColumnId,
	SpeDefColumnId,
	SpeedColumnId,
	StatTotalColumnId
};

struct ColumnInfo {
	std::string display_name;
	std::string query_name;
	bool togglable;
	int column_flags;
	int column_id;
	float column_width;
};

struct ColumnStatus {
	ColumnInfo column_info;
	bool enabled = false;

	ColumnStatus(ColumnInfo column, bool start_enabled) {
		column_info = column;
		enabled = start_enabled;
	}

	ColumnInfo GetColumnInfo() {
		return column_info;
	}

	bool IsEnabled() {
		return enabled;
	}
};

struct SubsetEntry {
	std::unordered_map<std::string, std::string> raw_entry_data;
	std::unordered_map<std::string, ParameterValue> converted_entry_data;

	void AddData(std::string label, std::string value) {
		raw_entry_data[label] = value;
	}

	std::string GetRawData(std::string label) {
		if (raw_entry_data.contains(label)) {
			return raw_entry_data[label];
		}
		return "No data found";
	}
	
	bool HasConvertedData(std::string label) {
		return converted_entry_data.contains(label);
	}

	std::string GetConvertedDataName(std::string label) {
		if (converted_entry_data.contains(label)) {
			ParameterValue param_val = converted_entry_data[label];
			return param_val.display_name;
		}
		return "CONVERTED DATA NOT FOUND";
	}

	ParameterValue GetParameterValue(std::string label) {
		if (converted_entry_data.contains(label)) {
			return converted_entry_data[label];
		}
		return ParameterValue();
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
			case NumberColumnId:
				delta = std::stoi(lhs.GetRawData("id")) - std::stoi(rhs.GetRawData("id"));
				break;
			case NameColumnId:
				delta = lhs.GetRawData("pretty_name").compare(rhs.GetRawData("pretty_name"));
				break;
			case DexColumnId:
				delta = std::stoi(lhs.GetRawData("dex_number")) - std::stoi(rhs.GetRawData("dex_number"));
				break;
			case ColorColumnId:
				delta = lhs.GetRawData("color").compare(rhs.GetRawData("color"));
				break;
			case ShapeColumnId:
				delta = lhs.GetRawData("shape").compare(rhs.GetRawData("shape"));
				break;
			case HeightColumnId:
				delta = std::stof(lhs.GetRawData("height")) - std::stof(rhs.GetRawData("height"));
				break;
			case WeightColumnId:
				delta = std::stod(lhs.GetRawData("weight")) - std::stod(rhs.GetRawData("weight"));
				break;
			case PrimaryTypeColumnId:
				delta = lhs.GetRawData("primary_type").compare(rhs.GetRawData("primary_type"));
				break;
			case SecondaryTypeColumnId:
				delta = lhs.GetRawData("secondary_type").compare(rhs.GetRawData("secondary_type"));
				break;
			case GenerationColumnId:
				delta = lhs.GetRawData("generation").compare(rhs.GetRawData("generation"));
				break;
			case FormSwitchColumnId:
				delta = std::stoi(lhs.GetRawData("form_switchable")) - std::stoi(rhs.GetRawData("form_switchable"));
				break;
			case GrowthRateColumnId:
				delta = lhs.GetRawData("growth_rate").compare(rhs.GetRawData("growth_rate"));
				break;
			case BaseExpColumnId:
				delta = std::stoi(lhs.GetRawData("base_experience")) - std::stoi(rhs.GetRawData("base_experience"));
				break;
			case BaseHappyColumnId:
				delta = std::stoi(lhs.GetRawData("base_happiness")) - std::stoi(rhs.GetRawData("base_happiness"));
				break;
			case CatchRateColumnId:
				delta = std::stoi(lhs.GetRawData("catch_rate")) - std::stoi(rhs.GetRawData("catch_rate"));
				break;
			case DimorphicColumnId:
				delta = std::stoi(lhs.GetRawData("dimorphic")) - std::stoi(rhs.GetRawData("dimorphic"));
				break;
			case PrimEggColumnId:
				delta = lhs.GetRawData("primary_egg_group").compare(rhs.GetRawData("primary_egg_group"));
				break;
			case SecEggColumnId:
				delta = lhs.GetRawData("secondary_egg_group").compare(rhs.GetRawData("secondary_egg_group"));
				break;
			case IsDefaultColumnId:
				delta = std::stoi(lhs.GetRawData("is_default")) - std::stoi(rhs.GetRawData("is_default"));
				break;
			case IsBabyColumnId:
				delta = std::stoi(lhs.GetRawData("is_baby")) - std::stoi(rhs.GetRawData("is_baby"));
				break;
			case IsLegendColumnId:
				delta = std::stoi(lhs.GetRawData("is_legendary")) - std::stoi(rhs.GetRawData("is_legendary"));
				break;
			case IsMythColumnId:
				delta = std::stoi(lhs.GetRawData("is_mythical")) - std::stoi(rhs.GetRawData("is_mythical"));
				break;
			case AbilOneColumnId:
				delta = lhs.GetRawData("ability_1").compare(rhs.GetRawData("ability_1"));
				break;
			case AbilTwoColumnId:
				delta = lhs.GetRawData("ability_2").compare(rhs.GetRawData("ability_2"));
				break;
			case AbilHiddenColumnId:
				delta = lhs.GetRawData("hidden_ability").compare(rhs.GetRawData("hidden_ability"));
				break;
			case HealthColumnId:
				delta = std::stoi(lhs.GetRawData("hp")) - std::stoi(rhs.GetRawData("hp"));
				break;
			case AttackColumnId:
				delta = std::stoi(lhs.GetRawData("attack")) - std::stoi(rhs.GetRawData("attack"));
				break;
			case DefenseColumnId:
				delta = std::stoi(lhs.GetRawData("defense")) - std::stoi(rhs.GetRawData("defense"));
				break;
			case SpeAtkColumnId:
				delta = std::stoi(lhs.GetRawData("special_attack")) - std::stoi(rhs.GetRawData("special_attack"));
				break;
			case SpeDefColumnId:
				delta = std::stoi(lhs.GetRawData("special_defense")) - std::stoi(rhs.GetRawData("special_defense"));
				break;
			case SpeedColumnId:
				delta = std::stoi(lhs.GetRawData("speed")) - std::stoi(rhs.GetRawData("speed"));
				break;
			case StatTotalColumnId:
				delta = std::stoi(lhs.GetRawData("stat_total")) - std::stoi(rhs.GetRawData("stat_total"));
				break;
			default:
				break;
			}
			if (delta > 0) {
				return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? 1 : 0;
			}
			else if (delta < 0) {
				return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? 0 : 1;
			}
		}
		return (std::stoi(lhs.GetRawData("id")) - std::stoi(rhs.GetRawData("id"))) < 0;
	}
};


// this struct is designed to allow for the conversion of a raw database column name to the associated 
// ParameterType to allow for access to the helpful display and formatting info not contained in the database info
struct ParameterTypeConverter {
private:
	std::unordered_map<std::string, ParameterType> column_type_map;

public:
	ParameterTypeConverter(std::unordered_map<std::string, ParameterType> column_type_mappings) {
		column_type_map = column_type_mappings;
	}

	
	ParameterType GetParamTypeByName(std::string col_name) {
		if (column_type_map.contains(col_name)) {
			return column_type_map[col_name];
		}
		return ParameterType();
	}

	// this seemingly redundant function simply reroutes requests using ColumnInfo ID values to column names
	ParameterType GetParamById(int col_id) {
		switch (col_id) {
		case NumberColumnId:
			return GetParamTypeByName("id");
		case NameColumnId:
			return GetParamTypeByName("pretty_name");
		case DexColumnId:
			return GetParamTypeByName("dex_number");
		case ColorColumnId:
			return GetParamTypeByName("color");
		case ShapeColumnId:
			return GetParamTypeByName("shape");
		case HeightColumnId:
			return GetParamTypeByName("height");
		case WeightColumnId:
			return GetParamTypeByName("weight");
		case PrimaryTypeColumnId:
			return GetParamTypeByName("primary_type");
		case SecondaryTypeColumnId:
			return GetParamTypeByName("secondary_type");
		case GenerationColumnId:
			return GetParamTypeByName("generation");
		case FormSwitchColumnId:
			return GetParamTypeByName("form_switchable");
		case GrowthRateColumnId:
			return GetParamTypeByName("growth_rate");
		case BaseExpColumnId:
			return GetParamTypeByName("base_experience");
		case BaseHappyColumnId:
			return GetParamTypeByName("base_happiness");
		case CatchRateColumnId:
			return GetParamTypeByName("catch_rate");
		case DimorphicColumnId:
			return GetParamTypeByName("dimorphic");
		case PrimEggColumnId:
			return GetParamTypeByName("primary_egg_group");
		case SecEggColumnId:
			return GetParamTypeByName("secondary_egg_group");
		case IsDefaultColumnId:
			return GetParamTypeByName("is_default");
		case IsBabyColumnId:
			return GetParamTypeByName("is_baby");
		case IsLegendColumnId:
			return GetParamTypeByName("is_legendary");
		case IsMythColumnId:
			return GetParamTypeByName("is_mythical");
		case AbilOneColumnId:
			return GetParamTypeByName("ability_1");
		case AbilTwoColumnId:
			return GetParamTypeByName("ability_2");
		case AbilHiddenColumnId:
			return GetParamTypeByName("hidden_ability");
		case HealthColumnId:
			return GetParamTypeByName("hp");
		case AttackColumnId:
			return GetParamTypeByName("attack");
		case DefenseColumnId:
			return GetParamTypeByName("defense");
		case SpeAtkColumnId:
			return GetParamTypeByName("special_attack");
		case SpeDefColumnId:
			return GetParamTypeByName("special_defense");
		case SpeedColumnId:
			return GetParamTypeByName("speed");
		case StatTotalColumnId:
			return GetParamTypeByName("stat_total");
		default:
			return ParameterType();
		}
	}
	
};

} //  namespace monster_calculator