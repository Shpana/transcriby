#include "transcribe_panel.h"

#include "imgui.h"

namespace transcriby::ui {
	TranscribePanel::TranscribePanel() {
	}

	void TranscribePanel::on_render() {
		ImGui::Begin("Transcribe");
		ImGui::End();
	}
}

