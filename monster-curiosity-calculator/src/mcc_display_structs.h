#pragma once
#include <string>

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

} //  namespace monster_calculator