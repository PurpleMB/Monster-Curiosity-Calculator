#pragma once

#include "mcc_communication_structs.h"

namespace monster_calculator {

// menu bar elements
void DrawMenuBarMenu(OutputEnvironment& output_environment);
void DrawMenuBarTools(OutputEnvironment& output_environment);
void DrawMenuBarHelp(OutputEnvironment& output_environment);

// menu windows
void DrawSettingsWindow(OutputEnvironment& output_environment);

// tools windows
void DrawDatabaseRebuildWindow(OutputEnvironment& output_environment);
void DrawProgramLogWindow(OutputEnvironment& output_environment);

// help windows
void DrawUserGuideWindow(OutputEnvironment& output_environment);
void DrawProgramInfoWindow(OutputEnvironment& output_environment);

} // namespace monster_calculator