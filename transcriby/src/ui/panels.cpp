#include "panels.h"

#include "ui/primitives.h"
#include "utils/convert_seconds_to_time_string.h"

namespace transcriby::ui {

#pragma region PlayerPanel

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
		std::string title = "Now playing..." + track.filename().string();
		ImGui::Text(title.c_str());
	}

	void PlayerPanel::_show_track_execution_configs() {
		auto info = _turntable.get_info();

		if (ImGui::SliderFloat("Volume", &info.volume, 0.0f, 1.0f))
			_turntable.set_volume(info.volume);

		if (ImGui::DragFloat("Play speed", &info.playback_speed, 0.1, 0.0f, 3.0f))
			_turntable.set_playback_speed(info.playback_speed);

		float position = (float)info.position / info.length;
		std::string time_view = convert_seconds_to_time_string(info.position / 1000);
		if (ImGui::SliderFloat(time_view.c_str(), &position, 0.0f, 1.0f)) {
			_turntable.set_position(position);
		}

		if (info.is_paused) {
			if (standart_button("Play"))
				_turntable.play();
		}
		else {
			if (standart_button("Pause"))
				_turntable.pause();
		}
	}

#pragma endregion

#pragma region PlaylistPanel

	PlaylistPanel::PlaylistPanel(Playlist& playlist)
		: _playlist(playlist) {
		_add_track_dialog.SetTitle("Choose file...");
		_add_track_dialog.SetTypeFilters({ ".mp3" });
	}

	void PlaylistPanel::on_render() {
		{
			ImGui::Begin("Playlist");
			_show_tracks();
			ImGui::Separator();
			_show_add_track_dialog();
			ImGui::End();
		}
		{
			_add_track_dialog.Display();
			if (_add_track_dialog.HasSelected()) {
				_playlist.add(_add_track_dialog.GetSelected());
				_add_track_dialog.ClearSelected();
			}
		}
	}

	void PlaylistPanel::_show_add_track_dialog() {
		if (standart_button("Add track")) {
			_add_track_dialog.Open();
		}
	}

	void PlaylistPanel::_show_tracks() {
		for (uint id = 0; id < _playlist.get_content().size(); ++id) {
			ImGui::PushID(id);
			auto track = _playlist.get_content().at(id);
			auto source = track.get_source();
			std::string track_name = source.filename().string();

			std::string state;
			if (track.get_state() == TranscribtionState::InQueue) {
				state = " (in queue...)";
			} else if (track.get_state() == TranscribtionState::InProgress) {
				state = " (in progress...)";
			} else if (track.get_state() == TranscribtionState::Ready) {
				state = u8" (ready)";
			}

			uint selected_id = _playlist.get_selected_id();
			if (ImGui::Selectable((track_name + state).c_str(), selected_id == id)) {
				if (selected_id == id)
					_playlist.unselect();
				else
					_playlist.select(id);
			}
			_show_track_manipulation_popup(id);
			ImGui::PopID();
		}
	}

	void PlaylistPanel::_show_track_manipulation_popup(uint id) {
		if (ImGui::BeginPopupContextItem("track_manipulation")) {
			ImGui::SeparatorText("Actions");
			if (standart_button("Remove")) {
				_playlist.remove(id);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

#pragma endregion

#pragma region TranscriberPanel

	TranscriberPanel::TranscriberPanel(Playlist& playlist) 
		: _playlist(playlist), _transcriber(playlist) {}

	void TranscriberPanel::on_render() {
		ImGui::Begin("Transcriber");
		if (_playlist.has_selected()) {
			if (standart_button("Transcribe")) {
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

#pragma endregion
}
