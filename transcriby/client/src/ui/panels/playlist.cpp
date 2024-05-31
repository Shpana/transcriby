#include "playlist.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace transcriby::ui {
	PlaylistPanel::PlaylistPanel(const Playlist& handle) {
		_handle = std::make_shared<Playlist>(handle);
	}

	void PlaylistPanel::on_render() {
		ImGui::Begin("Playlist");
		for (Track& elem : *_handle.get()) {
			ImGui::Button(elem.source.filename().string().c_str());
		}
		ImGui::End();
	}
}

