#pragma once

#include <memory>

#include "core/playlist.h"

namespace transcriby::ui {
	class PlaylistPanel {
	public:
		PlaylistPanel(const Playlist& handle);
		void on_render();
	private:
		std::shared_ptr<Playlist> _handle;
	};
}

