#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <misc/cpp/imgui_stdlib.h>

#include "mcc_imgui_helpers.h"

namespace monster_calculator {

float CenterNextElemByWidth(float element_width) {
	float content_size = ImGui::GetContentRegionAvail().x;
	float offset = (content_size - element_width) * 0.5f;
	if (offset > 0.0f) {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
	}

	return offset;
}

} // namespace monster_calculator