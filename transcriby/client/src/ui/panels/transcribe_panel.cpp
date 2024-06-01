#include "transcribe_panel.h"

#include "imgui.h"

namespace transcriby::ui {
	TranscribePanel::TranscribePanel(Playlist& playlist) 
		: _playlist(playlist) {}

	void TranscribePanel::on_render() {
		ImGui::Begin("Transcribe");
		ImGui::End();
	}
}

