// This class is meant to contain functions for common QoL operations with ImGui, such as calculating the offset required to center an element.
#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include <misc/cpp/imgui_stdlib.h>

namespace purple_mb::monster_calculator {

// Helper functions meant to place elements at certain positions on the current line
float CenterNextElem(float element_width);
float RightJustifyNextElem(float element_width);


} // namespace purple_mb::monster_calculator