#pragma once
#include <vector> // used by ParameterValue lists

#include "mcc_parameter_structs.h"

namespace monster_calculator {

// parameter values
extern const std::vector<ParameterValue> kTypeValuesList;

// enumerated parameters
extern const EnumeratedParameterType kPrimaryTypeParam;

// numerical parameter operations and values
extern const std::vector<ParameterValue> kStandardNumericalOperations;

// numerical parameters
extern const NumericalParameterType kHealthParam;

} //namespace monster_calculator