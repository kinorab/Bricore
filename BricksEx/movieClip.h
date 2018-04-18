#pragma once

#include "container.h"

namespace game {
	class MovieClip
		: public Container {
	public:
		MovieClip();
		virtual ~MovieClip() override;
		virtual int getCurrentFrame() const;
		virtual bool isPlaying() const;
		virtual void gotoAndPlay(int frame);
		virtual void gotoAndStop(int frame);
		virtual void nextFrame();
		virtual void play();
		virtual void prevFrame();
		virtual void stop();
		virtual int totalFrames();
	private:
		int currentFrame;
		bool playing;
	};
}
