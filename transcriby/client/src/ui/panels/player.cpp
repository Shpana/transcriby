#include "player.h"

namespace transcriby::ui {
	PlayerPanel::PlayerPanel(std::shared_ptr<PlaylistPanel> playlist) 
		: _playlist_panel(playlist) {
	}

	void PlayerPanel::on_render() {
		if (_playlist_panel->has_selection()) {
			if (_turntable.get_source() != _playlist_panel->get_selected()) {
				_turntable.try_put_track(_playlist_panel->get_selected());
			}
		}
		
		ImGui::Begin("Player");
		if (_turntable.has_track()) {
			if (ImGui::Button("Play")) {
				_turntable.play();
			}
			if (ImGui::Button("Pause")) {
				_turntable.pause();
			}
		}
		ImGui::End();
	}
}

