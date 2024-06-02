#pragma once

#include <memory>

#include "imgui.h"
#include "imfilebrowser.h"

#include "core/playlist.h"
#include "ui/panels/ipanel.h"

namespace transcriby::ui {
	class PlaylistPanel : public IPanel {
	public:
		PlaylistPanel(Playlist& playlist);
		void on_render() override;
	private:
		void _show_tracks();
		void _show_add_track_dialog();
		void _show_track_manipulation_popup(uint id);
	private:
		Playlist& _playlist;
		ImGui::FileBrowser _add_track_dialog;
	};
}

