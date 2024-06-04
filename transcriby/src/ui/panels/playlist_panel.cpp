#include "playlist_panel.h"

#include <algorithm>	

#include "imgui.h"

#include "ui/primitives.h"

namespace transcriby::ui {
	PlaylistPanel::PlaylistPanel(Playlist& playlist)
		: _playlist(playlist) {
		_add_track_dialog.SetTitle(u8"Выберите файл");
		_add_track_dialog.SetTypeFilters({ ".mp3", ".m4a"});
	}

	void PlaylistPanel::on_render() {
		{
			ImGui::Begin(u8"Плейлист");
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
		if (standart_button(u8"Добавить трек")) {
			_add_track_dialog.Open();
		}
	}

	void PlaylistPanel::_show_tracks() {
		for (uint id = 0; id < _playlist.get_content().size(); ++id) {
			ImGui::PushID(id);
			auto track = _playlist.get_content().at(id);
			auto source = track.get_source();
			std::string track_name = source.filename().string();

			uint selected_id = _playlist.get_selected_id();
			if (ImGui::Selectable(track_name.c_str(), selected_id == id)) {
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
			ImGui::SeparatorText(u8"Действия");
			if (standart_button(u8"Убрать")) {
				_playlist.remove(id);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}

