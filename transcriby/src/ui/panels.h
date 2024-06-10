#pragma once

#include "imgui.h"
#include "imfilebrowser.h"

#include "core/playlist.h"
#include "core/turntable.h"
#include "services/transcriber.h"

namespace transcriby::ui {
	class IPanel {
	public:
		virtual void on_render() = 0;
	};

#pragma region PlayerPanel

	class PlayerPanel : public IPanel {
	public:
		PlayerPanel(Playlist& playlist);
		void on_render() override;
	private:
		void _put_selected_track();
		void _show_playing_track();
		void _show_track_execution_configs();
	private:
		Playlist& _playlist;
		Turntable _turntable;
	};

#pragma endregion

#pragma region PlaylistPanel

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

#pragma endregion

#pragma region TranscriberPanel

	class TranscriberPanel : public IPanel {
	public:
		TranscriberPanel(Playlist& playlist);
		void on_render() override;
	private:
		Playlist& _playlist;
		TranscriberService _transcriber;
	};

#pragma endregion
}

