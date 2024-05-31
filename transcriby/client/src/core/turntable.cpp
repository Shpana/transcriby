#include "turntable.h"

namespace transcriby {
	Turntable::Turntable() {
		_engine = irrklang::createIrrKlangDevice();
	}

	Turntable::~Turntable() {
		_engine->drop();

		if (_sound)
			_sound->drop();
	}

	bool Turntable::try_put_track(const TrackSource& source) {
		if (_sound) {
			_sound->drop();
			_engine->removeSoundSource(_source.string().c_str());
		}
		_source = source;
		_sound = _engine->play2D(_source.string().c_str(), true, true);
		return _sound;
	}

	void Turntable::play() {
		if (_sound)
			_sound->setIsPaused(false);
	}

	void Turntable::pause() {
		if (_sound)
			_sound->setIsPaused(true);
	}
}

