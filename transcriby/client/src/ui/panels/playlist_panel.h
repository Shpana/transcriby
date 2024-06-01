#pragma once

#include <memory>

#include "imgui.h"
#include "imfilebrowser.h"

#include "core/playlist.h"

namespace transcriby::ui {
	class PlaylistPanel {
		using uint = uint64_t;
	public:
		PlaylistPanel(Playlist& playlist);
		void on_render();
	private:
		void _show_tracks();
		void _show_add_track_dialog();
		void _show_track_manipulation_popup(uint id);
	private:
		Playlist& _playlist;
		ImGui::FileBrowser _add_file_dialog;
	};
}

