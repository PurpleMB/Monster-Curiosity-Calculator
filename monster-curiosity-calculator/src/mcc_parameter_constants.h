#pragma once
#include <vector> // used by ParameterValue lists

#include "mcc_parameter_structs.h"

namespace monster_calculator {

// enumerated parameter values and operations
extern const std::vector<ParameterValue> kTypeValuesList;
extern const std::vector<ParameterValue> kBinaryValuesList;
extern const std::vector<ParameterValue> kColorValuesList;
extern const std::vector<ParameterValue> kShapeValuesList;
extern const std::vector<ParameterValue> kEggGroupValuesList;
extern const std::vector<ParameterValue> kGenerationValuesList;
extern const std::vector<ParameterValue> kGrowthRateValuesList;

extern const std::vector<ParameterOperation> kTextEnumOperations;
extern const std::vector<ParameterOperation> kValueEnumOperations;

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
extern const EnumeratedParameterType kGenerationParam;
extern const EnumeratedParameterType kGrowthRateParam;

// enumerated slider parameter values and operations
extern const std::vector<ParameterValue> kGenderRateValuesList;

extern const std::vector<ParameterOperation> kSliderEnumOperations;

// enumerated slider parameters
extern const SliderEnumeratedParameterType kGenderRateParam;

// open parameter values
extern const std::vector<ParameterOperation> kNameOperations;
extern const std::vector<ParameterOperation> kAbilityOperations;

extern const std::vector<DisplayColor> kOpenParamColors;

// open parameters
extern const OpenParameterType kNameParam;
extern const OpenParameterType kNormalAbilitiesParam;
extern const OpenParameterType kNormalAbilityOneParam;
extern const OpenParameterType kNormalAbilityTwoParam;
extern const OpenParameterType kHiddenAbilityParam;
extern const OpenParameterType kAnyAbilityParam;

// numerical parameter operations and values
extern const std::vector<ParameterOperation> kStandardNumericalOperations;

extern const std::vector<DisplayColor> kStandardStatColors;
extern const std::vector<float> kLinearThresholds;
extern const std::vector<float> kStandardStatThresholds;
extern const std::vector<float> kWeightThresholds;
extern const std::vector<float> kHeightThresholds;

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


// value calculation enum values
extern const std::vector<ParameterOperation> kValueOperations;
extern const std::vector<ParameterValue> kValueCalcEnums;

// value calculation types
extern const EnumeratedParameterType kValueCalcParam;

} // namespace monster_calculator