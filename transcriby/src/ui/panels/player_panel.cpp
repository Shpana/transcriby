#include "player_panel.h"

#include <string>
#include <iostream>

#include "imgui.h"

#include "ui/primitives.h"
#include "utils/convert_seconds_to_time_string.h"

namespace transcriby::ui {
	PlayerPanel::PlayerPanel(Playlist& playlist)
		: _playlist(playlist) {}

	void PlayerPanel::on_render() {
		_put_selected_track();
		
		ImGui::Begin(u8"Проигрыватель");
		if (_turntable.has_putted()) {
			_show_playing_track();
			_show_track_execution_configs();
		}
		ImGui::End();
	}

	void PlayerPanel::_put_selected_track() {
		if (_playlist.has_selected()) {
			auto source = _playlist.get_selected().get_source();
			if (_turntable.get_putted() != source)
				_turntable.put(source);
		} else {
			if (_turntable.has_putted())
				_turntable.extract();
		}
	}

	void PlayerPanel::_show_playing_track() {
		auto track = _turntable.get_putted();
		std::string title = u8"Сейчас игарет..." + track.filename().string();
		ImGui::Text(title.c_str());
	}

	void PlayerPanel::_show_track_execution_configs() {
		auto info = _turntable.get_info();

		if (ImGui::SliderFloat(u8"Звук", &info.volume, 0.0f, 1.0f))
			_turntable.set_volume(info.volume);

		if (ImGui::DragFloat(u8"Скорость", &info.playback_speed, 0.1, 0.0f, 3.0f))
			_turntable.set_playback_speed(info.playback_speed);

		float position = (float)info.position / info.length;
		std::string time_view = convert_seconds_to_time_string(info.position / 1000);
		if (ImGui::SliderFloat(time_view.c_str(), &position, 0.0f, 1.0f)) {
			_turntable.set_position(position);
		}

		if (info.is_paused) {
			if (standart_button(u8"Играть"))
				_turntable.play();
		}
		else {
			if (standart_button(u8"Пауза"))
				_turntable.pause();
		}
	}
}

