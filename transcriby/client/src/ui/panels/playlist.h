#pragma once

#include <memory>

#include "core/playlist.h"

namespace transcriby::ui {
	class PlaylistPanel {
	public:
		PlaylistPanel();
		void on_render();

		void add_track(const TrackSource& track);
		void pop_track(int id);

		int get_selected() { return _selected; }
		const Playlist& get_content() { return *_playlist.get(); }
	private:
		void _show_tracks();
		void _show_track_manipulation_popup(int id);
	private:
		int _selected = -1;
		std::unique_ptr<Playlist> _playlist;
	};
}

