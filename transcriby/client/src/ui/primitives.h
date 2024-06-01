#pragma once

#include <string>

#include "imgui.h"

namespace transcriby::ui {
	static float BUTTON_SIZE = 20.0f;

	inline bool standart_button(const std::string& title) {
		return ImGui::Button(title.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, BUTTON_SIZE));
	}
}

