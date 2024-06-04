#include "transcribe_panel.h"

#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

#include "imgui.h"

namespace transcriby::ui {
	TranscribePanel::TranscribePanel(Playlist& playlist) 
		: _playlist(playlist) {
		_playlist.on_removing_event.add_listener([](const Track& track) {
			std::cout << track.get_source().string() << std::endl;
		});
	}

	void TranscribePanel::on_render() {
		ImGui::Begin(u8"Расшифровщик");

		if (_playlist.has_selected()) {
			if (ImGui::Button(u8"Расшифровать")) {
				uint id = _playlist.get_selected_id();
				_queue.push_back(id);
				_playlist.change_state(id, TranscribtionState::InQueue);
			}

			auto& transcription = _playlist.get_selected().get_transcribtion();
			if (transcription != std::string())
				ImGui::Text(transcription.c_str());
		}
		ImGui::End();

		if (_current_id == -1) {
			if (!_queue.empty()) {
				_current_id = _queue.front();
				_queue.erase(_queue.begin());
				_playlist.change_state(_current_id, TranscribtionState::InProgress);

				auto& current = _playlist.get_content().at(_current_id);
				_transcriber_task =
					std::async(std::launch::async, [=]() {
						return _transcriber.translate_track(current.get_source().string());
					});
			}
		}

		// BUG: Handle server errors  
		if (_transcriber_task.valid()) {
			if (_transcriber_task.wait_for(0s) == std::future_status::ready) {
				_playlist.change_transcription(_current_id, _transcriber_task.get());
				_playlist.change_state(_current_id, TranscribtionState::Ready);
				_current_id = -1;
			}
		}
	}
}

