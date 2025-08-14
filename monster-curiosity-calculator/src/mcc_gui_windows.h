#pragma once

#include <vector>
#include <memory>

#include "mcc_structs.h"

namespace monster_calculator {

	void DrawWelcomeWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);
	void DrawSetParameterWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment, 
		std::vector<std::shared_ptr<ParameterType>> parameter_types);
	void DrawEnumeratorParameterSelector(EnumeratedParameterType& param_type, int& selected_subtype_index, QueryParameter& building_parameter);
	void DrawOpenParameterSelector(OpenParameterType& param_type, int& selected_subtype_index, QueryParameter& building_parameter);
	void DrawIntegerParameterSelector(IntegerParameterType& param_type, int& selected_subtype_index, QueryParameter& building_parameter);
	void DrawDecimalParameterSelector(DecimalParameterType& param_type, int& selected_subtype_index, QueryParameter& building_parameter);
	void DrawSubsetParameterTable(OutputEnvironment& output_environment);
	void DrawValueParameterWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);
	void DrawSetDisplayWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);
	void DrawOutputLogWindow(WindowParameters& window_parameters, OutputEnvironment& output_environment);

} // namespace monster_calculator
