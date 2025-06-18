#pragma once
#include "mcc_structs.h"

namespace monster_calculator {

	void DrawWelcomeWindow(WindowParameters& window_parameters);
	void DrawSetParameterWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);
	void DrawValueParameterWindow(WindowParameters& window_parameters);
	void DrawSetDisplayWindow(WindowParameters& window_parameters);
	void DrawOutputLogWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);

} // namespace monster_calculator
