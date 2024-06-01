#include "player_panel.h"

#include <string>
#include <iostream>

#include "imgui.h"

#include "ui/primitives.h"

namespace transcriby::ui {
	PlayerPanel::PlayerPanel(Playlist& playlist)
		: _playlist(playlist) {}

	void PlayerPanel::on_render() {
		_put_selected_track();
		
		ImGui::Begin("Player");
		if (_turntable.has_putted()) {
			_show_playing_track();
			_show_track_execution_configs();
		}
		ImGui::End();
	}

	void PlayerPanel::_put_selected_track() {
		if (_playlist.has_selected()) {
			if (_turntable.get_putted() != _playlist.get_selected())
				_turntable.put(_playlist.get_selected());
		} else {
			if (_turntable.has_putted())
				_turntable.extract();
		}
	}

	void PlayerPanel::_show_playing_track() {
		auto& track = _turntable.get_putted();
		std::string title = "Now playing..." + track.filename().string();
		ImGui::Text(title.c_str());
	}

	void PlayerPanel::_show_track_execution_configs() {
		auto info = _turntable.get_info();

		if (ImGui::SliderFloat("Volume", &info.volume, 0.0f, 1.0f))
			_turntable.set_volume(info.volume);

		if (ImGui::DragFloat("Speed", &info.playback_speed, 0.1, 0.0f, 3.0f))
			_turntable.set_playback_speed(info.playback_speed);

		float position = (float)info.position / info.length;
		if (ImGui::SliderFloat("Position", &position, 0.0f, 1.0f))
			_turntable.set_position(position);

		if (info.is_paused) {
			if (standart_button("Play"))
				_turntable.play();
		}
		else {
			if (standart_button("Pause"))
				_turntable.pause();
		}
	}
}

