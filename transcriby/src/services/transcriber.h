#pragma once

#include <string>
#include <future>
#include <vector>

#include "core/playlist.h"

namespace transcriby {
	struct TrackPassage {
		TrackSource source;
		// time in seconds
		int start;
		int end;
	};

	class TranscriberService {
	public:
		TranscriberService(Playlist& playlist);

		void add(uint id);
		void on_process();
		std::string translate_track(const TrackSource& track);
	private:
		std::vector<TrackPassage> _slice_by(const TrackSource& source, int gap);
	private:
		Playlist& _playlist;
		const std::string _service_url = "http://127.0.0.1:5000";

		std::vector<uint> _queue;
		uint _current_id = -1;

		std::vector<TrackPassage> _for_transcribtion;
		std::future<std::vector<TrackPassage>> _slicer_task;
		std::future<Passage> _transcriber_task;
	};
}

