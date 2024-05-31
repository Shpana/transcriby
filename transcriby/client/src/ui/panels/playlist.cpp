#include "playlist.h"

#include <algorithm>	

#include "imgui.h"
#include "imgui-SFML.h"

#include "ui/configs.h"

namespace transcriby::ui {
	PlaylistPanel::PlaylistPanel() {
		_playlist = std::make_unique<Playlist>();

		_add_file_dialog.SetTitle("Choose file...");
		_add_file_dialog.SetTypeFilters({ ".mp3" });
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
			_add_file_dialog.Display();
			if (_add_file_dialog.HasSelected()) {
				add_track(_add_file_dialog.GetSelected());
				_add_file_dialog.ClearSelected();
			}
		}
	}

	void PlaylistPanel::add_track(const TrackSource& track) {
		if (std::find(_playlist->begin(), _playlist->end(), track) == _playlist->end())
			_playlist->push_back(track);
	}

	void PlaylistPanel::pop_track(int id) {
		if (_selected_id == id)
			_selected_id = -1;
		_playlist->erase(_playlist->begin() + id);
	}

	void PlaylistPanel::_show_add_track_dialog() {
		if (ImGui::Button("Add Track", ImVec2(ImGui::GetContentRegionAvail().x, BUTTON_HEIGHT))) {
			_add_file_dialog.Open();
		}
	}

	void PlaylistPanel::_show_tracks() {
		for (int id = 0; id < _playlist->size(); ++id) {
			ImGui::PushID(id);
			std::string track_name = _playlist->at(id).filename().string();

			if (ImGui::Selectable(track_name.c_str(), _selected_id == id)) {
				_selected_id = (_selected_id == id) ? -1 : id;
			}

			_show_track_manipulation_popup(id);
			ImGui::PopID();
		}
	}

	void PlaylistPanel::_show_track_manipulation_popup(int id) {
		if (ImGui::BeginPopupContextItem("track_manipulation")) {
			ImGui::SeparatorText("Actions");
			if (ImGui::Button("Remove", ImVec2(ImGui::GetContentRegionAvail().x, BUTTON_HEIGHT))) {
				pop_track(id);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}

