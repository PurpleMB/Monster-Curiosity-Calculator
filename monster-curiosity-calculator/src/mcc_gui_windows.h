#pragma once
#include "mcc_structs.h"

namespace monster_calculator {

	void DrawWelcomeWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);
	void DrawSetParameterWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);
	void DrawEnumeratorParameterSelector(ParameterType& param_type, QueryParameter& building_parameter);
	void DrawNumericalParameterSelector(ParameterType& param_type, QueryParameter& building_parameter);
	void DrawSubsetParameterTable(OutputEnvironment& output_environment);
	void DrawValueParameterWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);
	void DrawSetDisplayWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);
	void DrawOutputLogWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);

} // namespace monster_calculator
