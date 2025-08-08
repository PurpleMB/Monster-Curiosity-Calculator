#pragma once
#include <vector> // used by ParameterValue lists

#include "mcc_parameter_structs.h"

namespace monster_calculator {

// parameter values
extern const std::vector<ParameterValue> kTypeValuesList;
extern const std::vector<ParameterValue> kBinaryValuesList;
extern const std::vector<ParameterValue> kColorValuesList;
extern const std::vector<ParameterValue> kShapeValuesList;
extern const std::vector<ParameterValue> kEggGroupValuesList;

// enumerated parameters
extern const EnumeratedParameterType kPrimaryTypeParam;
extern const EnumeratedParameterType kEitherTypeParam;
extern const EnumeratedParameterType kIsDefaultParam;
extern const EnumeratedParameterType kIsBabyParam;
extern const EnumeratedParameterType kColorParam;
extern const EnumeratedParameterType kShapeParam;
extern const EnumeratedParameterType kPrimaryEggParam;

// open parameter values
extern const std::vector<ParameterOperation> kNameOperations;

// open parameters
extern const OpenParameterType kNameParam;

// numerical parameter operations and values
extern const std::vector<ParameterValue> kStandardNumericalOperations;

// numerical parameters
extern const NumericalParameterType kDexNumParam;
extern const NumericalParameterType kCatchRateParam;
extern const NumericalParameterType kHealthParam;
extern const NumericalParameterType kAttackParam;
extern const NumericalParameterType kDefenseParam;
extern const NumericalParameterType kSpeAtkParam;
extern const NumericalParameterType kSpeDefParam;
extern const NumericalParameterType kSpeedParam;
extern const NumericalParameterType kStatTotalParam;

} //namespace monster_calculator