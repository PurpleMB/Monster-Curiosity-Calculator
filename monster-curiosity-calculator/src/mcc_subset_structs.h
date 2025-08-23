#pragma once
#include <string>
#include <iostream>
#include <unordered_map>

#include "mcc_parameter_structs.h"

namespace monster_calculator {

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
	GenderRateColumnId,
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
	bool colorable;
	int column_flags;
	int column_id;
	float column_width;
};

struct ColumnStatus {
	ColumnInfo column_info;
	bool display_enabled;
	bool coloring_enabled;

	ColumnStatus(ColumnInfo column) {
		column_info = column;
		display_enabled = false;
		coloring_enabled = false;
	}

	ColumnStatus(ColumnInfo column, bool start_enabled) {
		column_info = column;
		display_enabled = start_enabled;
		coloring_enabled = false;
	}

	ColumnStatus(ColumnInfo column, bool start_enabled, bool start_colored) {
		column_info = column;
		display_enabled = start_enabled;
		coloring_enabled = start_colored;
	}

	ColumnInfo GetColumnInfo() {
		return column_info;
	}

	bool IsEnabled() {
		return display_enabled;
	}

	bool IsColored() {
		return coloring_enabled;
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

	void AddConvertedData(std::string label, ParameterValue param_val) {
		converted_entry_data[label] = param_val;
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
				if (lhs.HasConvertedData("color") && rhs.HasConvertedData("color")) {
					delta = lhs.GetParameterValue("color").GetSortValue() - rhs.GetParameterValue("color").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("color").compare(rhs.GetRawData("color"));
				}
				break;
			case ShapeColumnId:
				if (lhs.HasConvertedData("shape") && rhs.HasConvertedData("shape")) {
					delta = lhs.GetParameterValue("shape").GetSortValue() - rhs.GetParameterValue("shape").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("shape").compare(rhs.GetRawData("shape"));
				}
				break;
			case HeightColumnId:
				delta = std::stof(lhs.GetRawData("height")) - std::stof(rhs.GetRawData("height"));
				break;
			case WeightColumnId:
				delta = std::stod(lhs.GetRawData("weight")) - std::stod(rhs.GetRawData("weight"));
				break;
			case PrimaryTypeColumnId:
				if (lhs.HasConvertedData("primary_type") && rhs.HasConvertedData("primary_type")) {
					delta = lhs.GetParameterValue("primary_type").GetSortValue() - rhs.GetParameterValue("primary_type").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("primary_type").compare(rhs.GetRawData("primary_type"));
				}
				break;
			case SecondaryTypeColumnId:
				if (lhs.HasConvertedData("secondary_type") && rhs.HasConvertedData("secondary_type")) {
					delta = lhs.GetParameterValue("secondary_type").GetSortValue() - rhs.GetParameterValue("secondary_type").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("secondary_type").compare(rhs.GetRawData("secondary_type"));
				}
				break;
			case GenerationColumnId:
				if (lhs.HasConvertedData("generation") && rhs.HasConvertedData("generation")) {
					delta = lhs.GetParameterValue("generation").GetSortValue() - rhs.GetParameterValue("generation").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("generation").compare(rhs.GetRawData("generation"));
				}
				break;
			case FormSwitchColumnId:
				if (lhs.HasConvertedData("form_switchable") && rhs.HasConvertedData("form_switchable")) {
					delta = lhs.GetParameterValue("form_switchable").GetSortValue() - rhs.GetParameterValue("form_switchable").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("form_switchable").compare(rhs.GetRawData("form_switchable"));
				}
				break;
			case GrowthRateColumnId:
				if (lhs.HasConvertedData("growth_rate") && rhs.HasConvertedData("growth_rate")) {
					delta = lhs.GetParameterValue("growth_rate").GetSortValue() - rhs.GetParameterValue("growth_rate").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("growth_rate").compare(rhs.GetRawData("growth_rate"));
				}
				break;
			case GenderRateColumnId:
				if (lhs.HasConvertedData("gender_rate") && rhs.HasConvertedData("gender_rate")) {
					delta = lhs.GetParameterValue("gender_rate").GetSortValue() - rhs.GetParameterValue("gender_rate").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("gender_rate").compare(rhs.GetRawData("gender_rate"));
				}
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
				if (lhs.HasConvertedData("dimorphic") && rhs.HasConvertedData("dimorphic")) {
					delta = lhs.GetParameterValue("dimorphic").GetSortValue() - rhs.GetParameterValue("dimorphic").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("dimorphic").compare(rhs.GetRawData("dimorphic"));
				}
				break;
			case PrimEggColumnId:
				if (lhs.HasConvertedData("primary_egg_group") && rhs.HasConvertedData("primary_egg_group")) {
					delta = lhs.GetParameterValue("primary_egg_group").GetSortValue() - rhs.GetParameterValue("primary_egg_group").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("primary_egg_group").compare(rhs.GetRawData("primary_egg_group"));
				}
				break;
			case SecEggColumnId:
				if (lhs.HasConvertedData("secondary_egg_group") && rhs.HasConvertedData("secondary_egg_group")) {
					delta = lhs.GetParameterValue("secondary_egg_group").GetSortValue() - rhs.GetParameterValue("secondary_egg_group").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("secondary_egg_group").compare(rhs.GetRawData("secondary_egg_group"));
				}
				break;
			case IsDefaultColumnId:
				if (lhs.HasConvertedData("is_default") && rhs.HasConvertedData("is_default")) {
					delta = lhs.GetParameterValue("is_default").GetSortValue() - rhs.GetParameterValue("is_default").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("is_default").compare(rhs.GetRawData("is_default"));
				}
				break;
			case IsBabyColumnId:
				if (lhs.HasConvertedData("is_baby") && rhs.HasConvertedData("is_baby")) {
					delta = lhs.GetParameterValue("is_baby").GetSortValue() - rhs.GetParameterValue("is_baby").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("is_baby").compare(rhs.GetRawData("is_baby"));
				}
				break;
			case IsLegendColumnId:
				if (lhs.HasConvertedData("is_legendary") && rhs.HasConvertedData("is_legendary")) {
					delta = lhs.GetParameterValue("is_legendary").GetSortValue() - rhs.GetParameterValue("is_legendary").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("is_legendary").compare(rhs.GetRawData("is_legendary"));
				}
				break;
			case IsMythColumnId:
				if (lhs.HasConvertedData("is_mythical") && rhs.HasConvertedData("is_mythical")) {
					delta = lhs.GetParameterValue("is_mythical").GetSortValue() - rhs.GetParameterValue("is_mythical").GetSortValue();
				}
				else {
					delta = lhs.GetRawData("is_mythical").compare(rhs.GetRawData("is_mythical"));
				}
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

} // namespace monster_calculator