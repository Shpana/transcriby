#include "player.h"

#include <string>

#include "ui/configs.h"

namespace transcriby::ui {
	PlayerPanel::PlayerPanel(std::shared_ptr<PlaylistPanel> playlist) 
		: _playlist_panel(playlist) {
	}

	void PlayerPanel::on_render() {
		if (_playlist_panel->has_selection()) {
			if (_turntable.get_source() != _playlist_panel->get_selected()) {
				_turntable.try_put_track(_playlist_panel->get_selected());
				_paused = true;
				_track_position = 0.0f;

				_turntable.set_volume(_volume);
				_turntable.set_speed(_speed);
			}
		}
		
		ImGui::Begin("Player");
		if (_turntable.has_track()) {
			ImGui::Text((std::string("Now putted down...") + _turntable.get_source().filename().string()).c_str());

			if (ImGui::SliderFloat("Volume", &_volume, 0.0f, 1.0f))
				_turntable.set_volume(_volume);
			if (ImGui::DragFloat("Speed", &_speed, 0.1, 0.0f, 3.0f))
				_turntable.set_speed(_speed);

			_track_position = (float)_turntable.get_position() / _turntable.get_length();
			if (ImGui::SliderFloat("Position", &_track_position, 0.0f, 1.0f)) {
				_turntable.set_positioin(_track_position);
			}

			if (_paused) {
				if (ImGui::Button("Play", ImVec2(ImGui::GetContentRegionAvail().x, BUTTON_HEIGHT))) {
					_paused = false;
					_turntable.play();
				}
			} else {
				if (ImGui::Button("Pause", ImVec2(ImGui::GetContentRegionAvail().x, BUTTON_HEIGHT))) {
					_paused = true;
					_turntable.pause();
				}
			}
		}
		ImGui::End();
	}
}

