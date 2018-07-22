#include "mouseHandler.h"
#include "../definition/utility.h"
#include "../definition/gameState.h"
#include "../interact/container.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
	MouseHandler::MouseHandler(const std::shared_ptr<const sf::RenderWindow> window) noexcept 
		: c_window(std::move(window)) {
	}

	void MouseHandler::handle(const sf::Event & event, Container & thing) {
		handleMouse(event, thing);
		if (event.type == sf::Event::MouseMoved) {
			handleMouseMoved(event, thing);
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			handleMouseButtonPressed(event, thing);
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			handleMouseButtonReleased(event, thing);
		}
	}

	void MouseHandler::handleMouseMoved(const sf::Event & event, Container & thing) {
		if (!previousContactNode) {
			return;
		}
		previousContactNode->dispatchEvent(MouseMovedEvent(event.mouseMove));
	}

	void MouseHandler::handleMouseButtonPressed(const sf::Event & event, Container & thing) {
		if (!previousContactNode) {
			return;
		}
		previousContactNode->dispatchEvent(MousePressedEvent(event.mouseButton));
	}

	void MouseHandler::handleMouseButtonReleased(const sf::Event & event, Container & thing) {
		if (!previousContactNode) {
			return;
		}
		previousContactNode->dispatchEvent(MouseReleasedEvent(event.mouseButton));
	}

	void MouseHandler::handleMouseWheelScrolled(const sf::Event & event, Container & thing) {
		if (!previousContactNode) {
			return;
		}
		previousContactNode->dispatchEvent(MouseWheelScrolledEvent(event.mouseWheelScroll));
	}

	void MouseHandler::handleMouse(const sf::Event & event, Container & thing) {
		const sf::Vector2f & mousePosition(sf::Vector2f(sf::Mouse::getPosition(*c_window)));
		std::shared_ptr<InteractiveObject> contactNode;
		if (mousePosition.x < 0 || mousePosition.x > GAME_WIDTH
			|| mousePosition.y < 0 || mousePosition.y > GAME_HEIGHT) {
			contactNode = nullptr;
		}
		else {
			contactNode = thing.getObjectUnderPoint(mousePosition);
			if (contactNode) {
				contactNode->dispatchEvent(MouseInSightEvent(c_window));
			}
		}

		if (contactNode != previousContactNode) {
			std::vector<std::shared_ptr<InteractiveObject>> previousNodes;
			for (std::shared_ptr<InteractiveObject> node = previousContactNode; node;) {
				previousNodes.push_back(node);
				Container * parent = node->getParent();
				if (parent) {
					node = parent->shared_from_this();
				}
				else {
					node = nullptr;
				}
			}

			std::vector<std::shared_ptr<InteractiveObject>> currentNodes;
			for (std::shared_ptr<InteractiveObject> node = contactNode; node;) {
				currentNodes.push_back(node);
				Container * parent = node->getParent();
				if (parent) {
					node = parent->shared_from_this();
				}
				else {
					node = nullptr;
				}
			}

			int sameNodeCount = 0;
			if (previousContactNode && contactNode) {
				while (*(previousNodes.rbegin() + sameNodeCount) == *(currentNodes.rbegin() + sameNodeCount)) {
					sameNodeCount += 1;
				}
			}
			// handle mouse left
			std::for_each(previousNodes.begin(), previousNodes.end() - sameNodeCount,
				[&](std::shared_ptr<InteractiveObject> & node) {
				node->dispatchEvent(MouseLeftEvent());
			});
			// handle mouse enter
			std::for_each(currentNodes.begin(), currentNodes.end() - sameNodeCount,
				[&](std::shared_ptr<InteractiveObject> & node) {
				node->dispatchEvent(MouseEnteredEvent());
			});

			previousContactNode = contactNode;
		}
	}
}