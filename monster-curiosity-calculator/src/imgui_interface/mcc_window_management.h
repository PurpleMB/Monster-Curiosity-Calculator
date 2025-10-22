#pragma once

#include "../data_communication/mcc_communication_structs.h"

namespace purple_mb::monster_calculator {

void BeginStyledWindow(WindowParameters& window_parameters);
void EndStyledWindow(WindowParameters& window_parameters);

void BeginSubMenuWindow(WindowParameters& window_parameters, bool* p_open);
void EndSubMenuWindow(WindowParameters& window_parameters);

// these functions are meant to create windows that will dynamically resize to occupy a region of the screen indicated by the position vectors.
// ex: a window with the vectors of (0.25f, 0.25f), (0.75f, 0.75f) will occupy the middle 50% of the screen
void BeginScalingWindow(WindowParameters& window_parameters, ImVec2 starting_pos, ImVec2 ending_pos);
void EndScalingWindow(WindowParameters& window_parameters);

// these functions are meant to improve over the above scaling window functions by allowing for constant margins and scaling relative to a defined pivot point
void BeginPivotScaledWindow(WindowParameters& window_parameters, ImVec2 pivot, ImVec2 pivot_offset, ImVec2 window_size_percent);
void EndPivotScaledWindow(WindowParameters& window_parameters);

} // namespace purple_mb::monster_calculator
