#pragma once
#include <string>

#include "imgui.h"-
#include "imgui_impl_win32.h"
#include <misc/cpp/imgui_stdlib.h>

#include "mcc_imgui_helpers.h"

namespace purple_mb::monster_calculator {

float CenterNextElem(float element_width) {
	float content_size = ImGui::GetContentRegionAvail().x;
	float offset = (content_size - element_width) * 0.5f;
	if (offset > 0.0f) {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
	}

	return offset;
}

float RightJustifyNextElem(float element_width) {
	float content_size = ImGui::GetContentRegionAvail().x;
	float offset = (content_size - element_width);
	if (offset > 0.0f) {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
	}

	return offset;
}

} // namespace purple_mb::monster_calculator