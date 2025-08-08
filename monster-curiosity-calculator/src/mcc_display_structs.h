#pragma once
#include <string>

#include "imgui.h" // for acces to ImVec4 datatype

namespace monster_calculator {

struct DisplayColor {
private:
	std::string color_name;
	ImVec4 color_value;

public:
	DisplayColor(std::string name, ImVec4 values) {
		color_name = name;
		color_value = values;
	}

	std::string GetColorName() {
		return color_name;
	}

	ImVec4 GetColorValues() {
		return color_value;
	}
};

} //  namespace monster_calculator