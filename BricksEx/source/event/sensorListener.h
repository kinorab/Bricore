#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class SensorListener :
		public EventListener {
	public:
		explicit SensorListener(std::function<void(SensorEvent *)> callback);
		virtual ~SensorListener() = default;
		virtual void visit(SensorEvent * visitable) override;
	private:
		std::function<void(SensorEvent *)> callback;
	};
}
