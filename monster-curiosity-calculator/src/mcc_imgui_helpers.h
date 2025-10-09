// This class is meant to contain functions for common QoL operations with ImGui, such as calculating the offset required to center an element.
#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <misc/cpp/imgui_stdlib.h>

namespace monster_calculator {

float CenterNextElemByWidth(float element_width);

} // namespace monster_calculator