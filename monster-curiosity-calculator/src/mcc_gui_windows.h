#pragma once
#include "mcc_gui_window_structs.h"

namespace monster_calculator {
	void DrawWelcomeWindow(WindowParameters& window_parameters, const char* database_path, const char* json_path);
	void DrawSetParameterWindow(WindowParameters& window_parameters);
	void DrawValueParameterWindow(WindowParameters& window_parameters, const char* database_path);
	void DrawSetDisplayWindow(WindowParameters& window_parameters);
	void DrawOutputLogWindow(WindowParameters& window_parameters);
} // namespace monster_calculator
