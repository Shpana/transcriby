#pragma once

#include <memory>

#include "core/turntable.h"
#include "ui/panels/playlist.h"

namespace transcriby::ui {
	class PlayerPanel {
	public:
		PlayerPanel(std::shared_ptr<PlaylistPanel> playlist);
		void on_render();
	private:
		Turntable _turntable;
		std::shared_ptr<PlaylistPanel> _playlist_panel;
	};
}

