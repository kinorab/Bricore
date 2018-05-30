#include "movieClip.h"

namespace game {
	MovieClip::MovieClip() {
	}

	MovieClip::~MovieClip() {
	}

	int MovieClip::getCurrentFrame() const {
		return currentFrame;
	}

	bool MovieClip::isPlaying() const {
		return playing;
	}

	void MovieClip::gotoAndPlay(int frame) {
	}

	void MovieClip::gotoAndStop(int frame) {
	}

	void MovieClip::nextFrame() {
	}

	void MovieClip::play() {
	}

	void MovieClip::prevFrame()	{
	}

	void MovieClip::stop() {
	}

	int MovieClip::totalFrames() {
		return 0;
	}
}