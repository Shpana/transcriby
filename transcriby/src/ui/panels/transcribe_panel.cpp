#include "transcribe_panel.h"

#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

#include "imgui.h"

#include "ui/primitives.h"
#include "utils/convert_seconds_to_time_string.h"

namespace transcriby::ui {
	TranscribePanel::TranscribePanel(Playlist& playlist) 
		: _playlist(playlist), _transcriber(playlist) {}

	void TranscribePanel::on_render() {
		ImGui::Begin(u8"Расшифровщик");
		if (_playlist.has_selected()) {
			if (standart_button(u8"Расшифровать")) {
				uint id = _playlist.get_selected_id();
				_transcriber.add(id);
				_playlist.change_state(id, TranscribtionState::InQueue);
			}

			for (auto& elem : _playlist.get_selected().get_transcribtion()) {
				ImGui::PushID(&elem);
				ImGui::Text(convert_seconds_to_time_string(elem.start).c_str());
				ImGui::SameLine();
				if (ImGui::Selectable(elem.transcribtion.c_str(), false)) {
				}
				ImGui::PopID();
			}
		}
		ImGui::End();
		_transcriber.on_process();
	}
}

