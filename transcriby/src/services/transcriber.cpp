#include "transcriber.h"

#include <assert.h>
#include <chrono>
#include <unordered_map>
using namespace std::chrono_literals;

#include "cpr/cpr.h"

namespace transcriby {
	TranscriberService::TranscriberService(Playlist& playlist)
		: _playlist(playlist) {
		_playlist.on_removing_event.add_listener([&](const Track& track) {
				if (_current_id == _playlist.get_track_id(track)) {
					_playlist.change_state(_current_id, TranscribtionState::None);
					_current_id = -1;
				}
			});
	}

	void TranscriberService::add(uint id) {
		if (std::find(_queue.begin(), _queue.end(), id) == _queue.end())
			_queue.push_back(id);
	}

	void TranscriberService::on_process() {
		if (_current_id == -1) {
			if (!_queue.empty()) {
				_current_id = _queue.front();
				_queue.erase(_queue.begin());
				_playlist.change_state(_current_id, TranscribtionState::InProgress);

				auto& current = _playlist.get_content().at(_current_id);
				auto& source = current.get_source();

				_slicer_task = std::async(std::launch::async,
					[=]() -> std::vector<TrackPassage> {
						return _slice_by(source, 10);
					});
			}
		}

		if (_slicer_task.valid()) {
			if (_slicer_task.wait_for(0s) == std::future_status::ready) {
				for (auto& elem : _slicer_task.get()) {
					_for_transcribtion.push_back(elem);
				}
			}
		}

		if (!_for_transcribtion.empty()) {
			if (!_transcriber_task.valid()) {
				auto& elem = _for_transcribtion.at(0);
				_transcriber_task = std::async(std::launch::async,
					[=]() -> Passage {
						return Passage{ translate_track(elem.source), elem.start, elem.end };
					});
				_for_transcribtion.erase(_for_transcribtion.begin());
			}
		}

		if (_transcriber_task.valid()) {
			if (_transcriber_task.wait_for(0s) == std::future_status::ready) {
				_playlist.add_passage_transcribtion(_current_id, _transcriber_task.get());
				if (_for_transcribtion.empty()) {
					_playlist.change_state(_current_id, TranscribtionState::Ready);
					_current_id = -1;
				}
			}
		}
	}

	std::string TranscriberService::translate_track(const TrackSource& track) {
		cpr::Response response = cpr::Post(
			cpr::Url(_service_url), 
			cpr::Multipart{ {"passage", cpr::File{track.string()}} });

		if (response.status_code == 200)
			return response.text;
		else
			assert(false);
	}
	
	std::vector<TrackPassage> TranscriberService::_slice_by(
			const TrackSource& source, int gap) {
		std::vector<TrackPassage> result;

		std::hash<std::string> hasher;
		std::string path = "C:/Dev/transcriby/transcriby/.local/" + std::to_string(hasher(source.string()));
		std::filesystem::create_directory(path);
		std::string command =
			"ffmpeg -i " + source.string() + " -f segment -segment_time " 
				+ std::to_string(gap) + " -c copy " + path + "/%03d.mp3";
		system(command.c_str());
		int i = 0;
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			result.push_back({entry.path(), i * gap, (i + 1) * gap});
			++i;
		}
		return result;
	}
}

