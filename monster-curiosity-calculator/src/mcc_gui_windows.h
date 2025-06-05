#pragma once

namespace monster_calculator {
	void DrawWelcomeWindow(const int window_settings, const char* database_path, const char* json_path);
	void DrawSetParameterWindow(const int window_settings);
	void DrawValueParameterWindow();
	void DrawSetDisplayWindow();
	void DrawOutputLogWindow(const int window_settings);
} // namespace monster_calculator
