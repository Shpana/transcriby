#pragma once

#include "core/playlist.h"
#include "ui/panels/ipanel.h"

namespace transcriby::ui {
	class TranscribePanel : public IPanel {
	public:
		TranscribePanel(Playlist& playlist);
		void on_render() override;
	private:
		Playlist& _playlist;
	};
}

