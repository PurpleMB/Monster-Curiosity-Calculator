#pragma once

#include "mcc_communication_structs.h"

namespace monster_calculator {

void BeginStyledWindow(WindowParameters& window_parameters);
void EndStyledWindow(WindowParameters& window_parameters);

void BeginDynamicWindow(WindowParameters& window_parameters, bool* p_open);
void EndDynamicWindow(WindowParameters& window_parameters);

} // namespace monster_calculator
