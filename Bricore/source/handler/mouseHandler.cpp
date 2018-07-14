#include "mouseHandler.h"
#include "../definition/utility.h"
#include "../definition/gameState.h"
#include "../interact/container.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
	MouseHandler::MouseHandler(const std::shared_ptr<const sf::RenderWindow> window) noexcept 
		: c_window(std::move(window)){
	}

	void MouseHandler::handle(const sf::Event & event, Container & target) {
		handleMouse(event, target);
		if (event.type == sf::Event::MouseMoved) {
			handleMouseMove(event, target);
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			handleMouseButtonPressed(event, target);
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			handleMouseButtonReleased(event, target);
		}
	}

	void MouseHandler::handleMouseMove(const sf::Event & event, Container & target) {
	}

	void MouseHandler::handleMouseButtonPressed(const sf::Event & event, Container & target) {
		if (!previousContactNode) {
			return;
		}
		previousContactNode->dispatchEvent(MousePressedEvent(event.mouseButton));
	}

	void MouseHandler::handleMouseButtonReleased(const sf::Event & event, Container & target) {
		if (!previousContactNode) {
			return;
		}
		previousContactNode->dispatchEvent(MouseReleasedEvent(event.mouseButton));
	}

	void MouseHandler::handleMouse(const sf::Event & event, Container & target) {
		const sf::Vector2i & mousePosition(sf::Mouse::getPosition(*c_window));
		std::shared_ptr<InteractiveObject> contactNode;
		if (mousePosition.x < 0 || mousePosition.x > GAME_WIDTH
			|| mousePosition.y < 0 || mousePosition.y > GAME_HEIGHT) {
			contactNode = nullptr;
		}
		else {
			contactNode = target.getObjectUnderPoint(sf::Vector2f(mousePosition));
			if (contactNode) {
				contactNode->dispatchEvent(MouseMovedEvent(c_window));
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

			std::for_each(previousNodes.begin(), previousNodes.end() - sameNodeCount,
				[&](std::shared_ptr<InteractiveObject> & node) {
				node->dispatchEvent(MouseLeftEvent());
			});

			std::for_each(currentNodes.begin(), currentNodes.end() - sameNodeCount,
				[&](std::shared_ptr<InteractiveObject> & node) {
				node->dispatchEvent(MouseEnteredEvent());
			});

			previousContactNode = contactNode;
		}
	}
}