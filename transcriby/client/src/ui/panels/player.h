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
		bool _paused = true;
		float _speed = 1.0f;
		float _volume = 1.0f;
		float _track_position = 0.0f;
		Turntable _turntable;
		std::shared_ptr<PlaylistPanel> _playlist_panel;
	};
}

