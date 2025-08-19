#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

#include "imgui.h" // for acces to ImVec4 datatype

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
	SecondaryTypeColumnId
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
			case NumberColumnId:
				delta = std::stoi(lhs.GetData("id")) - std::stoi(rhs.GetData("id"));
				break;
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

} //  namespace monster_calculator