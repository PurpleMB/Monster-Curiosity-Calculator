#pragma once
#include <string>
#include <stdlib.h>

#include "imgui.h"

namespace monster_calculator {
typedef struct WindowParameters {
	std::string name = "";
	ImVec2 window_size;
	ImVec2 window_position;
	int imgui_window_settings = 0;
};
} // namespace monster_calculator