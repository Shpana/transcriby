#pragma once

#include <future>
#include <string>
#include <vector>

#include "core/playlist.h"
#include "services/transcriber.h"
#include "ui/panels/ipanel.h"

namespace transcriby::ui {
	class TranscribePanel : public IPanel {
	public:
		TranscribePanel(Playlist& playlist);
		void on_render() override;
	private:
		Playlist& _playlist;

		std::vector<uint> _queue;
		uint _current_id = -1;

		std::string _transcribtion;
		TranscriberService _transcriber;
		std::future<std::string> _transcriber_task;
	};
}

