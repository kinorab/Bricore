#include "SFMLMouseHandler.h"
#include "../definition/utility.h"
#include "mouse/mouseEvent.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace game {
	SFMLMouseHandler::SFMLMouseHandler(const sf::Vector2i clientSize) :
		clientSize(clientSize) {
	}

	void SFMLMouseHandler::handle(const sf::Event & event, Container & target, const bool isTargetFullScreen) {
		if (event.type == sf::Event::MouseMoved) {
			handleMouseMove(event, target, isTargetFullScreen);
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			handleMouseButtonPressed(event, target);
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			handleMouseButtonReleased(event, target);
		}
		else if (event.type == sf::Event::MouseLeft) {
			handleMouseLeft(event, target, isTargetFullScreen);
		}
	}

	void SFMLMouseHandler::handleMouseButtonPressed(const sf::Event & event, Container & target) {
		if (!previousContactNode) {
			return;
		}

		previousContactNode->dispatchEvent(MousePressedEvent(event.mouseButton));
	}

	void SFMLMouseHandler::handleMouseButtonReleased(const sf::Event & event, Container & target) {
		if (!previousContactNode) {
			return;
		}

		previousContactNode->dispatchEvent(MouseReleasedEvent(event.mouseButton));
	}

	void SFMLMouseHandler::handleMouseLeft(const sf::Event & event, Container & target, const bool isTargetFullScreen) {
		sf::Event newEvent;
		newEvent.type = sf::Event::MouseMoved;
		newEvent.mouseMove = { -1, -1 };
		handleMouseMove(newEvent, target, isTargetFullScreen);
	}

	void SFMLMouseHandler::handleMouseMove(const sf::Event & event, Container & target, const bool isTargetFullScreen) {
		const sf::Vector2i & mousePosition{ event.mouseMove.x, event.mouseMove.y };
		std::shared_ptr<InteractiveObject> contactNode;
		if (mousePosition.x < 0 || mousePosition.x > clientSize.x
			|| mousePosition.y < 0 || mousePosition.y > clientSize.y) {
			contactNode = nullptr;
		}
		else if (isTargetFullScreen) {
			target.dispatchEvent(MouseMovedEvent(event.mouseMove));
			contactNode.reset(new RectangleShapeNode(
				std::make_shared<sf::RectangleShape>(static_cast<sf::Vector2f>(clientSize)
					)));
		}
		else {
			contactNode = target.getObjectUnderPoint(sf::Vector2f(mousePosition));
			if (contactNode) {
				contactNode->dispatchEvent(MouseMovedEvent(event.mouseMove));
			}
		}

		if (isTargetFullScreen) {
			if (contactNode) {
				target.dispatchEvent(MouseEnteredEvent());
			}
			else {
				target.dispatchEvent(MouseLeftEvent());
			}
			if (contactNode != previousContactNode) {
				previousContactNode.reset(new Container(target));
			}
			return;
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