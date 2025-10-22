#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "../data_communication/mcc_communication_structs.h"

#include "mcc_gui_widgets.h"

namespace purple_mb::monster_calculator {

void DrawHelpIcon(std::string help_text, OutputEnvironment& environment) {
	ImTextureID help_icon_tex = environment.GetTextureFromMap("help");

	float line_height = ImGui::GetTextLineHeight();
	float spacing_height = (ImGui::GetTextLineHeightWithSpacing() - line_height);
	ImVec2 icon_size = ImVec2(line_height, line_height);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing_height);

	ImVec4 tint_col = kGrayColor.EvaluateColorWithIntensity(1.0f);
	ImVec4 border_col = kClearColor.EvaluateColorWithIntensity(0.0f);

	ImGui::Image(help_icon_tex, icon_size, ImVec2(0.0f, 0.0), ImVec2(1.0f, 1.0f), tint_col, border_col);
	ImGui::SetItemTooltip(help_text.c_str());
}

} // namespace purple_mb::monster_calculator