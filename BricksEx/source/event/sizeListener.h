#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class SizeListener :
		public EventListener {
	public:
		explicit SizeListener(std::function<void(SizeEvent *)> callback);
		virtual ~SizeListener() = default;
		virtual void visit(SizeEvent * visitable) override;
	private:
		std::function<void(SizeEvent *)> callback;
	};
}
