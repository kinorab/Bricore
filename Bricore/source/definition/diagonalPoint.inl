#include "diagonalPoint.h"

template<typename T>
inline sys::DPoint<T>::DPoint(const sf::Vector2<T> &D1, const sf::Vector2<T> &D2) {
	if (D1 == D2) {
		throw std::invalid_argument("Two points are not diagonal points");
	}
	dot1 = D1;
	dot2 = D2;
}

template<typename T>
inline sys::DPoint<T>::DPoint(sf::Vector2<T>&& D1, sf::Vector2<T>&& D2) {
	if (D1 == D2) {
		throw std::invalid_argument("Two points are not diagonal points");
	}
	dot1 = D1;
	dot2 = D2;
}

template<typename T>
inline sys::DPoint<T>::DPoint(const sf::Rect<T>& rect)
	: dot1(rect.left, rect.top)
	, dot2(rect.left + rect.width, rect.top + rect.height) {
}

template<typename T>
inline sys::DPoint<T>::DPoint(sf::Rect<T>&& rect)
	: dot1(rect.left, rect.top)
	, dot2(rect.left + rect.width, rect.top + rect.height) {
}

template<typename T>
inline sys::DPoint<T>& sys::DPoint<T>::operator =(const DPoint<T>& right) {
	dot1 = right.dot1;
	dot2 = right.dot2;
	return *this;
}

template<typename T>
inline sys::DPoint<T>& sys::DPoint<T>::operator =(DPoint<T>&& right) {
	dot1 = right.dot1;
	dot2 = right.dot2;
	return *this;
}

template<typename T>
template<typename U>
inline sys::DPoint<T>::DPoint(const DPoint<U>& vector)
	:dot1(sf::Vector2<T>(vector.dot1)), dot2(sf::Vector2<T>(vector.dot2)) {
}

// display each point
template<typename T>
inline std::ostream & sys::operator<<(std::ostream & os, const DPoint<T>& vector) {
	os << "Dot1(" << vector.dot1.x << ", " << vector.dot1.y << ")	"
		<< "Dot2(" << vector.dot2.x << ", " << vector.dot2.y << ")";
	return os;
}

// add each diagonalPoint X and Y with Vector(X, Y) 
template<typename T>
inline sys::DPoint<T> sys::operator +(const DPoint<T>& left, const sf::Vector2<T>& right) {
	return DPoint<T>(left.dot1 + right, left.dot2 + right);
}
// add each diagonalPoint X and Y with Vector(X, Y) 
template<typename T>
inline sys::DPoint<T> sys::operator +(const sf::Vector2<T>& left, const DPoint<T>& right) {
	return DPoint<T>(left + right.dot1, left + right.dot2);
}
// add each diagonalPoint X and Y with value
template<typename T>
inline sys::DPoint<T> sys::operator +(const DPoint<T>& left, const T right) {
	return DPoint<T>(sf::Vector2<T>(left.dot1.x + right, left.dot1.y + right)
		, sf::Vector2<T>(left.dot2.x + right, left.dot2.y + right));
}
// add each diagonalPoint X and Y with value
template<typename T>
inline sys::DPoint<T> sys::operator +(const T left, const DPoint<T>& right) {
	return DPoint<T>(sf::Vector2<T>(right.dot1.x + left, right.dot1.y + left)
		, sf::Vector2<T>(right.dot2.x + left, right.dot2.y + left));
}

// subtract each diagonalPoint X and Y with Vector(X, Y) 
template<typename T>
inline sys::DPoint<T> sys::operator -(const DPoint<T>& left, const sf::Vector2<T>& right) {
	return DPoint<T>(left.dot1 - right, left.dot2 - right);
}

// subtract each diagonalPoint X and Y with value
template<typename T>
inline sys::DPoint<T> sys::operator -(const DPoint<T>& left, const T right) {
	return DPoint<T>(sf::Vector2<T>(left.dot1.x - right, left.dot1.y - right)
		, sf::Vector2<T>(left.dot2.x - right, left.dot2.y - right));
}

// multiply each diagonalPoint X and Y with value
template<typename T>
inline sys::DPoint<T> sys::operator *(const DPoint<T>& left, const T right) {
	return DPoint<T>(left.dot1 * right, left.dot2 * right);
}

// divide each diagonalPoint X and Y with value
template<typename T>
inline sys::DPoint<T> sys::operator /(const DPoint<T>& left, const T right) {
	return DPoint<T>(left.dot1 / right, left.dot2 / right);
}

// increase each diagonalPoint X and Y with Vector(X, Y)
template<typename T>
inline sys::DPoint<T>& sys::operator +=(DPoint<T>& left, const sf::Vector2<T>& right) {
	left.dot1 += right;
	left.dot2 += right;
	return left;
}
// increase each diagonalPoint X and Y with value
template<typename T>
inline sys::DPoint<T>& sys::operator +=(DPoint<T>& left, const T right) {
	left.dot1.x += right;
	left.dot1.y += right;
	left.dot2.x += right;
	left.dot2.y += right;
	return left;
}

// decrease each diagonalPoint X and Y with Vector(X, Y) 
template<typename T>
inline sys::DPoint<T>& sys::operator -=(DPoint<T>& left, const sf::Vector2<T>& right) {
	left.dot1 -= right;
	left.dot2 -= right;
	return left;
}
// decrease each diagonalPoint X and Y with value 
template<typename T>
inline sys::DPoint<T>& sys::operator -=(DPoint<T>& left, const T right) {
	left.dot1.x -= right;
	left.dot1.y -= right;
	left.dot2.x -= right;
	left.dot2.y -= right;
	return left;
}

// multiply each diagonalPoint X and Y with value
template<typename T>
inline sys::DPoint<T>& sys::operator *=(DPoint<T>& left, const T right) {
	left.dot1 *= right;
	left.dot2 *= right;
	return left;
}

// divide each diagonalPoint X and Y with value
template<typename T>
inline sys::DPoint<T>& sys::operator /=(DPoint<T>& left, const T right) {
	left.dot1 /= right;
	left.dot2 /= right;
	return left;
}

// compare equal two diagonalPoints with each dots
template<typename T>
bool sys::operator ==(const DPoint<T>& left, const DPoint<T>& right) {
	return (left.dot1 == right.dot1) && (left.dot2 == left.dot2);
}

// compare unequal two diagonalPoints with each dots
template<typename T>
inline bool sys::operator !=(const DPoint<T>& left, const DPoint<T>& right) {
	return (left.dot1 != right.dot1) || (left.dot2 != right.dot2);
}
