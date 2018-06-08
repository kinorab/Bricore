#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class SizeEvent;
	class SizeListener :
		public EventListener {
	public:
		explicit SizeListener(std::function<void(SizeEvent *)> callback);
		virtual ~SizeListener() = default;
		virtual void visit(SizeEvent * visitable);
	private:
		std::function<void(SizeEvent *)> callback;
	};
}
