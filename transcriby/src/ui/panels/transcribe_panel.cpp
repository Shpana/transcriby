#include "transcribe_panel.h"

#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

#include "imgui.h"

namespace transcriby::ui {
	TranscribePanel::TranscribePanel(Playlist& playlist) 
		: _playlist(playlist) {}

	void TranscribePanel::on_render() {
		ImGui::Begin("Transcribe");
		if (_playlist.has_selected()) {
			auto selected = _playlist.get_selected();

			if (ImGui::Button("Transcribe"))
				_transcriber_task =
					std::async(std::launch::async, [=]() {
						return _transcriber.translate_track(selected);
					});
		}
		ImGui::End();

		if (_transcriber_task.valid())
			if (_transcriber_task.wait_for(0s) == std::future_status::ready)
				std::cout << _transcriber_task.get() << std::endl;
	}
}

