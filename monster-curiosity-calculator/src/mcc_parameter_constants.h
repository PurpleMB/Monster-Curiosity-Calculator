#pragma once
#include <vector> // used by ParameterValue lists

#include "mcc_parameter_structs.h"

namespace monster_calculator {

// parameter values
extern const std::vector<ParameterValue> kTypeValuesList;

// enumerated parameters
extern const ParameterType kPrimaryTypeParam;

// numerical parameters
extern const ParameterType kHealthParam;

} //namespace monster_calculator