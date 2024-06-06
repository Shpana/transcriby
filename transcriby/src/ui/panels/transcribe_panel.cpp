#include "transcribe_panel.h"

#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

#include "imgui.h"

namespace transcriby::ui {
	TranscribePanel::TranscribePanel(Playlist& playlist) 
		: _playlist(playlist), _transcriber(playlist) {}

	void TranscribePanel::on_render() {
		ImGui::Begin(u8"Расшифровщик");
		if (_playlist.has_selected()) {
			if (ImGui::Button(u8"Расшифровать")) {
				uint id = _playlist.get_selected_id();
				_transcriber.add(id);
				_playlist.change_state(id, TranscribtionState::InQueue);
			}

			for (auto& elem : _playlist.get_selected().get_transcribtion()) {
				ImGui::Text(elem.transcribtion.c_str());
			}
		}
		ImGui::End();
		_transcriber.on_process();
	}
}

