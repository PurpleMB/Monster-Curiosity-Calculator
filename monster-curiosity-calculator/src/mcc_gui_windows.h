#pragma once
namespace monster_calculator {
	void DrawWelcomeWindow(const int windowSettings, const char* databasePath, const char* jsonPath);
	void DrawSetParameterWindow(const int windowSettings);
	void DrawValueParameterWindow();
	void DrawSetDisplayWindow();
	void DrawOutputLogWindow(const int windowSettings);
} // namespace monster_calculator
