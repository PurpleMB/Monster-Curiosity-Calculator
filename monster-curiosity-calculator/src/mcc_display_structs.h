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

	static DisplayColor InterpolateColors(DisplayColor color_a, DisplayColor color_b, float t) {
		std::string blend_name = color_a.GetColorName() + "-" + color_b.GetColorName() + " Blend";
		ImVec4 color_a_vals = color_a.GetColorValues();
		ImVec4 color_b_vals = color_b.GetColorValues();
		ImVec4 blend_values = ImVec4(
			color_a_vals.x * (1 - t) + color_b_vals.x * t,
			color_a_vals.y * (1 - t) + color_b_vals.y * t,
			color_a_vals.z * (1 - t) + color_b_vals.z * t,
			color_a_vals.w * (1 - t) + color_b_vals.w * t
		);

		DisplayColor color_blend = DisplayColor(
			blend_name, blend_values
		);
		return color_blend;
	}
};

struct TableCellDisplayInfo {
private:
	std::string column_text;
	DisplayColor column_color;

public:
	TableCellDisplayInfo() {
		column_text = "UNINITIALIZED COLUMN TEXT";
		column_color = DisplayColor();
	}

	TableCellDisplayInfo(std::string text, DisplayColor color) {
		column_text = text;
		column_color = color;
	}

	std::string GetText() const {
		return column_text;
	}

	DisplayColor GetColor() const {
		return column_color;
	}
};

struct WindowParameters {
	std::string name;
	ImVec2 window_size;
	ImVec2 window_position;
	int imgui_window_settings;
	float internal_margin;
};

} //  namespace monster_calculator