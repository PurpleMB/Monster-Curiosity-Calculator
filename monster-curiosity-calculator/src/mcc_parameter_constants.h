#pragma once
#include <vector> // used by ParameterValue lists

#include "mcc_parameter_structs.h"

namespace monster_calculator {

// parameter values and operations
extern const std::vector<ParameterValue> kTypeValuesList;
extern const std::vector<ParameterValue> kBinaryValuesList;
extern const std::vector<ParameterValue> kColorValuesList;
extern const std::vector<ParameterValue> kShapeValuesList;
extern const std::vector<ParameterValue> kEggGroupValuesList;

extern const std::vector<ParameterOperation> kEnumOperations;

// enumerated parameters
extern const EnumeratedParameterType kPrimaryTypeParam;
extern const EnumeratedParameterType kSecondaryTypeParam;
extern const EnumeratedParameterType kEitherTypeParam;
extern const EnumeratedParameterType kDimorphicParam;
extern const EnumeratedParameterType kIsDefaultParam;
extern const EnumeratedParameterType kCanSwitchParam;
extern const EnumeratedParameterType kIsBabyParam;
extern const EnumeratedParameterType kIsLegendParam;
extern const EnumeratedParameterType kIsMythicParam;
extern const EnumeratedParameterType kColorParam;
extern const EnumeratedParameterType kShapeParam;
extern const EnumeratedParameterType kPrimaryEggParam;
extern const EnumeratedParameterType kSecondaryEggParam;

// open parameter values
extern const std::vector<ParameterOperation> kNameOperations;
extern const std::vector<ParameterOperation> kAbilityOperations;

// open parameters
extern const OpenParameterType kNameParam;
extern const OpenParameterType kAbilityParam;
extern const OpenParameterType kHiddenAbilityParam;
extern const OpenParameterType kAnyAbilityParam;

// numerical parameter operations and values
extern const std::vector<ParameterValue> kStandardNumericalOperations;

// integer parameters
extern const IntegerParameterType kDexNumParam;
extern const IntegerParameterType kBaseExpParam;
extern const IntegerParameterType kBaseHappyParam;
extern const IntegerParameterType kCatchRateParam;
extern const IntegerParameterType kHatchCountParam;
extern const IntegerParameterType kHealthParam;
extern const IntegerParameterType kAttackParam;
extern const IntegerParameterType kDefenseParam;
extern const IntegerParameterType kSpeAtkParam;
extern const IntegerParameterType kSpeDefParam;
extern const IntegerParameterType kSpeedParam;
extern const IntegerParameterType kStatTotalParam;

// decimal parameters
extern const DecimalParameterType kWeightParam;
extern const DecimalParameterType kHeightParam;

} //namespace monster_calculator