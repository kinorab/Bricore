// exclude 4-points edge frame
template<typename T>
extern const bool EXCIntersects(const sf::Rect<T> &a, const sf::Rect<T> &b) {

	const sf::Vector2<T> ALT(a.left, a.top);
	const sf::Vector2<T> ARB(a.left + a.width, a.top + a.height);
	const sf::Vector2<T> BLT(b.left, b.top);
	const sf::Vector2<T> BRB(b.left + b.width, b.top + b.height);

	if (ARB.x > BLT.x && ARB.y > BLT.y
		&& ALT.x < BRB.x && ALT.y < BRB.y) {
		return true;
	}
	return false;
}
// include 4-points edge frame
template<typename T>
extern const bool INCIntersects(const sf::Rect<T> &a, const sf::Rect<T> &b) {

	const sf::Vector2<T> ALT(a.left, a.top);
	const sf::Vector2<T> ARB(a.left + a.width, a.top + a.height);
	const sf::Vector2<T> BLT(b.left, b.top);
	const sf::Vector2<T> BRB(b.left + b.width, b.top + b.height);

	if (ARB.x >= BLT.x && ARB.y >= BLT.y
		&& ALT.x <= BRB.x && ALT.y <= BRB.y) {
		return true;
	}
	return false;
}

template<typename T>
extern const bool pointIntersects(const sf::Vector2<T> &point, const sf::Rect<T> &block) {

	const sf::Vector2<T> LT(block.left, block.top);
	const sf::Vector2<T> RB(block.left + block.width, block.top + block.height);

	if (point.x >= LT.x && point.x <= RB.x
		&& point.y >= LT.y && point.y <= RB.y) {
		return true;
	}
	return false;
}

template<typename T>
extern const bool ballIntersects(const sf::Vector2<T> &APos, const T &ARadius, const sf::Vector2<T> &BPos, const T &BRadius) {
	
	const T distance = std::sqrt(std::pow(APos.x - BPos.x, 2) + std::pow(APos.y - BPos.y, 2));

	if (distance <= ARadius + BRadius) {
		return true;
	}
	return false;
}

template<typename T>
extern const T ballDistance(const sf::Vector2<T> &APos, const T &ARadius, const sf::Vector2<T> &BPos, const T &BRadius) {

	const T distance = std::sqrt(std::pow(APos.x - BPos.x, 2) + std::pow(APos.y - BPos.y, 2)) - (ARadius + BRadius);
	return distance;
}