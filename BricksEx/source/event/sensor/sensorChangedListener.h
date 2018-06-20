#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class SensorChangedEvent;
	class SensorChangedListener :
		public EventListener {
	public:
		explicit SensorChangedListener(std::function<void(SensorChangedEvent &)> callback);
		virtual ~SensorChangedListener() = default;
		virtual void visit(SensorChangedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(SensorChangedEvent &)> callback;
	};
}
