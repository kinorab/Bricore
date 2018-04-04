#include "define.h"
// exclude 4-points edge frame
template<typename T>
const bool game::EXCintersects(const sf::Rect<T>& a, const sf::Rect<T>& b) {

	sf::Vector2<T> ALT(a.left, a.top);
	sf::Vector2<T> ART(a.left + a.width, a.top);
	sf::Vector2<T> ALB(a.left, a.top + a.height);
	sf::Vector2<T> ARB(a.left + a.width, a.top + a.height);

	sf::Vector2<T> BLT(b.left, b.top);
	sf::Vector2<T> BRT(b.left + b.width, b.top);
	sf::Vector2<T> BLB(b.left, b.top + b.height);
	sf::Vector2<T> BRB(b.left + b.width, b.top + b.height);

	if (ARB.x > BLT.x && ARB.y > BLT.y
		&& ALT.x < BRB.x && ALT.y < BRB.y) {
		return true;
	}
	else if (ALB.x < BRT.x && ALB.y > BRT.y
		&& ART.x > BLB.x && ART.y < BLB.y) {
		return true;
	}
	return false;
}
// include 4-points edge frame
template<typename T>
const bool game::INCintersects(const sf::Rect<T>& a, const sf::Rect<T>& b) {

	sf::Vector2<T> ALT(a.left, a.top);
	sf::Vector2<T> ART(a.left + a.width, a.top);
	sf::Vector2<T> ALB(a.left, a.top + a.height);
	sf::Vector2<T> ARB(a.left + a.width, a.top + a.height);

	sf::Vector2<T> BLT(b.left, b.top);
	sf::Vector2<T> BRT(b.left + b.width, b.top);
	sf::Vector2<T> BLB(b.left, b.top + b.height);
	sf::Vector2<T> BRB(b.left + b.width, b.top + b.height);

	if (ARB.x >= BLT.x && ARB.y >= BLT.y
		&& ALT.x <= BRB.x && ALT.y <= BRB.y) {
		return true;
	}
	else if (ALB.x <= BRT.x && ALB.y >= BRT.y
		&& ART.x >= BLB.x && ART.y <= BLB.y) {
		return true;
	}
	return false;
}

template<typename T>
const bool game::pointIntersects(const sf::Vector2<T>& point, const sf::Rect<T>& block) {

	sf::Vector2<T> LT(block.left, block.top);
	sf::Vector2<T> RB(block.left + block.width, block.top + block.height);

	if (point.x >= LT.x && point.x <= RB.y
		&& point.y >= LT.y && point.y <= RB.y) {
		return true;
	}
	return false;
}
