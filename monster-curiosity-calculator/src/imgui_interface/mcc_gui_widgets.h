#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "../mcc_communication_structs.h"

namespace purple_mb::monster_calculator {

void DrawHelpIcon(std::string help_text, OutputEnvironment& environment);

} // namespace purple_mb::monster_calculator