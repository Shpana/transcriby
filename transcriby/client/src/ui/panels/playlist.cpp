#include "playlist.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "ui/configs.h"

namespace transcriby::ui {
	PlaylistPanel::PlaylistPanel() {
		_playlist = std::make_unique<Playlist>();
	}

	void PlaylistPanel::on_render() {
		ImGui::Begin("Playlist");
		_show_tracks();
		ImGui::Separator();
		if (ImGui::Button("Add Track", ImVec2(ImGui::GetContentRegionAvail().x, BUTTON_HEIGHT))) {
			// TODO: Track search dialog
		}
		ImGui::End();
	}

	void PlaylistPanel::add_track(const TrackSource& track) {
		_playlist->push_back(track);
	}

	void PlaylistPanel::pop_track(int id) {
		if (_selected == id)
			_selected = -1;
		_playlist->erase(_playlist->begin() + id);
	}

	void PlaylistPanel::_show_tracks() {
		for (int id = 0; id < _playlist->size(); ++id) {
			ImGui::PushID(id);
			std::string track_name = _playlist->at(id).filename().string();

			if (ImGui::Selectable(track_name.c_str(), _selected == id)) {
				_selected = (_selected == id) ? -1 : id;
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

