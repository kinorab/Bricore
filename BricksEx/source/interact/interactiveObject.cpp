#include "interactiveObject.h"
#include "../event/UIEvent.h"
#include "../event/dispatchHelper.h"
#include "container.h"
#include "../definition/utility.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace game {
	InteractiveObject::InteractiveObject() :
		enabled(true) {
		onEnabled();
	}

	InteractiveObject::~InteractiveObject() {
	}

	void InteractiveObject::dispatchEvent(UIEvent & event) {
		DispatchHelper helper(event);
		helper.setCurrentTarget(this);

		if (event.getPhase() == EventPhase::NONE) {
			helper.setTarget(this);
			helper.setPhase(EventPhase::AT_TARGET);
		}

		auto listenerRange = listeners.equal_range(event.getType());
		std::vector<std::pair<const EventType, std::pair<const int, std::shared_ptr<EventListener>>>> tempListeners;
		std::copy(listenerRange.first, listenerRange.second, std::back_inserter(tempListeners));
		std::for_each(tempListeners.begin(), tempListeners.end(),
			[&](std::pair<const EventType, std::pair<const int, std::shared_ptr<EventListener>>> & listener) {
			event.accept(*listener.second.second);
		});

		if (event.getPhase() == EventPhase::AT_TARGET) {
			helper.setPhase(EventPhase::BUBBLING_PHASE);
		}

		if (event.getPhase() == EventPhase::BUBBLING_PHASE
			&& event.getBubbles()
			&& parent != nullptr
			&& !helper.isPropagationStopped()) {
			parent->dispatchEvent(event);
		}

		if (event.getTarget() == this) {
			helper.setPhase(EventPhase::NONE);
			helper.setCurrentTarget(nullptr);
		}
	}

	bool InteractiveObject::getEnabled() const {
		return enabled;
	}

	Container * InteractiveObject::getParent() {
		return parent;
	}

	void InteractiveObject::onDisabled() {
	}

	void InteractiveObject::onEnabled() {
	}

	void InteractiveObject::setEnabled(bool value) {
		if (value == enabled) {
			return;
		}

		if (value) {
			onEnabled();
		}
		else {
			onDisabled();
		}

		enabled = value;
	}

	void InteractiveObject::setParent(Container * container) {
		parent = container;
	}

	void InteractiveObject::update(const float) {
	}

	void InteractiveObject::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		target.draw(*getDrawable(), states.transform.combine(getTransform()));
	}
}