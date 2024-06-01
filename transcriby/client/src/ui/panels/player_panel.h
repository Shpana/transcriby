#pragma once

#include <memory>

#include "core/playlist.h"
#include "core/turntable.h"
#include "ui/panels/ipanel.h"

namespace transcriby::ui {
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
}

